#pragma once

#include "Ray.h"
#include "Scene.h"
#include "Buffer.h"
#include "../Utility/ThreadPool.h"

namespace krt {

	struct KRT_API TraceProgress {
		int current;
		int total;
		TraceProgress(int cur, int tol) :current(cur), total(tol) {}
	};

	struct KRT_API TraceState {
		int threadNum;

		int taskNum;
		
		std::vector<TraceProgress> progress;
	};

	class KRT_API RayTracer {
	public:
		RayTracer(Ref<Scene> scene, int samplerNumbers, int depth);

		~RayTracer();

		void Start(ImageBuffer& imgBuffer, bool isMulti_Thread, int unit_height = 256);

		void Shutdown();

		const TraceState& GetState() const { return *m_State; }

	private:
		static glm::vec3 fragTracer(Scene& scene, const glm::vec2& uv);

		struct TaskParam {
			Scene& scene;

			ImageBuffer& imgBuffer;

			TraceProgress& progress;

			int width, height;
			int start_h, end_h;

			int sampler;

			int depth;

			bool* isTracing;
		};

		static void traceTask(Ref<TaskParam> param);

	private:
		Ref<Scene> m_Scene;

		ThreadPool* m_ThreadPool;

		TraceState* m_State;

		int m_SamplerNumbers;

		int m_Depth;

		bool isTracing;

	};

}