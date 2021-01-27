UINT vps = 1;
WNDPROC original_windowproc = nullptr;

bool sdk_initialized = false;
bool timer_initialized = false;

float timeSinceStartup = 0;
float timeFrequency = 0;
float get_time_since_startup() {
	LARGE_INTEGER PerformanceCount;
	LARGE_INTEGER FrequencyCount;

	if (!timer_initialized) {
		timer_initialized = true;

		PerformanceCount.QuadPart = 0;
		QueryPerformanceCounter(&PerformanceCount);

		FrequencyCount.QuadPart = 0;
		QueryPerformanceFrequency(&FrequencyCount);

		timeFrequency = float(FrequencyCount.QuadPart);

		timeSinceStartup = float(PerformanceCount.QuadPart);
	}

	PerformanceCount.QuadPart = 0;
	QueryPerformanceCounter(&PerformanceCount);

	return float(PerformanceCount.QuadPart - timeSinceStartup) / timeFrequency;
}
class LogSystem {
public:
	static inline int max_entries = 10;

	static void draw_text(Vector2, std::wstring);

	struct LogEntry {
	public:
		std::wstring message;
		float startedAt;
		float duration;

		LogEntry(std::wstring message, float duration) {
			this->message = message;
			this->duration = duration;
			this->startedAt = get_time_since_startup();
		}
	};

	static inline std::vector<LogEntry> logs = std::vector<LogEntry>();

	static void Log(std::wstring message, float duration) {
		if (logs.size() >= max_entries)
			logs.erase(logs.begin());

		logs.push_back(LogEntry(message, duration));
	}

	static void Render() {
		float yPos = 30.0f;
		for (int i = 0; i < logs.size(); i++) {
			LogEntry entry = logs[i];
			if ((get_time_since_startup() - entry.startedAt) >= entry.duration) {
				logs.erase(logs.begin() + i);
				continue;
			}

			draw_text(Vector2(200, yPos), entry.message);

			yPos += 15.0f;
		}
	}
};
void LogSystem::draw_text(Vector2 pos, std::wstring str) {
	Renderer::String(pos, str.c_str(), D2D1::ColorF::White, true);
}