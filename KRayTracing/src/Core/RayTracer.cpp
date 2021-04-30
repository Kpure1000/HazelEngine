#include "krtpch.h"

#include "../../include/Core/RayTracer.h"
#include "../../include/Utility/KRTMath.h"

#include <ctime>

namespace krt {

	RayTracer::RayTracer(Ref<Scene> scene, int samplerNumbers, int depth)
		: m_Scene(scene), m_SamplerNumbers(samplerNumbers), m_Depth(depth) {

		int coreNum;
#if defined KRT_PLATFORM_WINDOWS
		SYSTEM_INFO systemInfo;
		GetSystemInfo(&systemInfo);
		coreNum = (int)(systemInfo.dwNumberOfProcessors);
#else 
		coreNum = 2;
#endif // KRT_PLATFORM_WINDOWS

		m_State = new TraceState();

		m_State->threadNum = coreNum - 2;

		m_ThreadPool = new ThreadPool(m_State->threadNum);

	}

	RayTracer::~RayTracer() {
		//delete m_ThreadPool;
		
		// MUST discon after thread pool!!!
		//delete m_State;

	}

	void RayTracer::Start(ImageBuffer& imgBuffer, bool isMulti_Thread, int unit_height) {
		isTracing = true;
		int width = m_Scene->GetSize().x, height = m_Scene->GetSize().y;
		if (isMulti_Thread) {
			int splitNum = height / unit_height;
			m_State->taskNum = height % unit_height ? splitNum + 1 : splitNum;
			int tmpHeight = height;
			for (int i = 0; i < m_State->taskNum; i++) {
				if (tmpHeight < unit_height) {
					m_State->progress.emplace_back(0, width * tmpHeight * m_SamplerNumbers);
				}
				else {
					m_State->progress.emplace_back(0, width * unit_height * m_SamplerNumbers);
				}
				tmpHeight -= unit_height;
			}
			int h_start = 0;
			for (int i = 0; i < m_State->taskNum; i++) {
				m_ThreadPool->Submit(traceTask, std::make_shared<TaskParam>(
					TaskParam{ *m_Scene, imgBuffer, m_State->progress[i], width, height,
					h_start, h_start += unit_height, m_SamplerNumbers, m_Depth,&isTracing }));
			}
		}
		else {
			m_State->taskNum = 1;
			m_State->progress.push_back({ 0, width * height * m_SamplerNumbers });

			m_ThreadPool->Submit(traceTask, std::make_shared<TaskParam>(TaskParam{
				*m_Scene, imgBuffer, m_State->progress[0], width, height, 0, height, m_SamplerNumbers, m_Depth,&isTracing }));
		}
	}

	void RayTracer::Shutdown()
	{
		isTracing = false;
	}

	glm::vec3 RayTracer::fragTracer(Scene& scene, const glm::vec2& uv) {
		HitRecord rec;
		auto ray = scene.GetCamera()->GetRay(uv);
		if (scene.GetObjects()->Hit(ray, 0.001f, 1e20f, rec)) {
			return 0.5f * (rec.normal + glm::vec3(1.0f));
		}
		else {
			return scene.GetSky(glm::normalize(ray.Direct()));
		}
	}

	void RayTracer::traceTask(Ref<TaskParam> param) {
		glm::vec2 uv;
		glm::vec3 fragColor;
		if (!*(param->isTracing))return;
		for (int h = param->start_h; h < param->height && h < param->end_h; h++) {
			for (int w = 0; w < param->width; w++) {
				for (int s = 0; s < param->sampler; s++) {
					if (!*(param->isTracing))return;
					// Get uv
					uv = {
						float(w + KRTMath::Drand48()) / float(param->width),
						float(h + KRTMath::Drand48()) / float(param->height)
					};
					// Trace ray
					fragColor += RayTracer::fragTracer(param->scene, uv);
					param->progress.current++;
				}
				fragColor /= (float)param->sampler;
				// Write frag color
				param->imgBuffer.WritePixel(glm::ivec2(w, h), fragColor);
				fragColor = glm::vec3(0.0f);
			}
		}
	}

}
