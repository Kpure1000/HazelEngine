#include "hzpch.h"

#include "Instrumentor.h"

#include "Hazel/Core/Log.h"

#include <sstream>
#include <iomanip>

namespace hazel
{
	///////////////////////////
	/// InstrumentContainer
	///////////////////////////

	bool InstrumentContainer::Begin(const std::string filePath)
	{
		m_OutputStream.open(filePath);
		return m_OutputStream.is_open();
	}

	void InstrumentContainer::End()
	{
		m_OutputStream.close();
	}

	void InstrumentContainer::WriteFileContent(const ProfileResult& result)
	{
		m_Container.at(curContainer).at(curResult) = result;
		curResult++;
		if (curResult == maxSize)
		{
			savingContainer = curContainer;
			curContainer = (curContainer + 1) % maxContainerSize;
			curResult = 0;
			SaveProfile();
		}
	}

	void InstrumentContainer::WriteFileFooter()
	{
		int tmpIndex = 0;
		savingContainer = curContainer;
		while (tmpIndex < curResult)
		{
			auto& result = m_Container.at(savingContainer).at(tmpIndex);

			std::stringstream json;

			json << std::setprecision(3) << std::fixed;
			json << ",\n{";
			json << "\"cat\":\"function\",";
			json << "\"dur\":" << (result.elapsedTime.count()) << ',';
			json << "\"name\":\"" << result.name << "\",";
			json << "\"ph\":\"X\",";
			json << "\"pid\":0,";
			json << "\"tid\":" << result.threadID << ",";
			json << "\"ts\":" << result.start.count();
			json << "}";

			m_OutputStream << json.str();
			m_OutputStream.flush();

			tmpIndex++;
		}

		m_OutputStream << "]}";
		m_OutputStream.flush();
	}

	void InstrumentContainer::SaveProfile()
	{
		m_ThreadPool.Submit([this]
			{
				LogTimer threadCreatingTime("Write File");
				int tmpIndex = 0;
				while (tmpIndex < maxSize)
				{
					auto& result = m_Container.at(savingContainer).at(tmpIndex);

					std::stringstream json;

					json << std::setprecision(3) << std::fixed;
					json << ",\n{";
					json << "\"cat\":\"function\",";
					json << "\"dur\":" << (result.elapsedTime.count()) << ',';
					json << "\"name\":\"" << result.name << "\",";
					json << "\"ph\":\"X\",";
					json << "\"pid\":0,";
					json << "\"tid\":" << result.threadID << ",";
					json << "\"ts\":" << result.start.count();
					json << "}";

					m_OutputStream << json.str();
					m_OutputStream.flush();

					tmpIndex++;
				}
			});

	}

	///////////////////////////
	/// Instrumentor
	///////////////////////////

	void Instrumentor::BeginSession(const std::string& name, const std::string& filePath)
	{
		std::lock_guard lock(m_Mutex);
		if (m_CurrentSession)
		{
			if (Log::GetCoreLogger())
			{
				Log::ErrorCore("Instrument::BeginSession('{0}') when session '{1}' already open.",
					name, m_CurrentSession->name);
			}
			InternalEndSession();
		}
		if (InstrumentContainer::GetInstance().Begin(filePath))
		{
			m_CurrentSession = new InstrumentationSession({ name });
			WriteHeader();
		}
		else
		{
			if (Log::GetCoreLogger())
			{
				Log::ErrorCore("Instrument could not open results file '{0}'.", filePath);
			}
		}
	}

	void Instrumentor::EndSession()
	{
		std::lock_guard lock(m_Mutex);
		InternalEndSession();
	}

	void Instrumentor::WriteProfile(const ProfileResult& result)
	{
		{
			std::lock_guard lock(m_Mutex);
			if (m_CurrentSession)
			{
				InstrumentContainer::GetInstance().WriteFileContent(result);
			}
		}

	}

	void Instrumentor::InternalEndSession()
	{
		if (m_CurrentSession)
		{
			WriteFooter();

			InstrumentContainer::GetInstance().End();

			delete m_CurrentSession;
			m_CurrentSession = nullptr;
		}
	}
}