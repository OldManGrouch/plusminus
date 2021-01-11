
namespace hwid {
	std::string winname;
	std::string webhook_url = c_xor("https://discord.com/api/webhooks/782872540724199464/UClxJ-olKhhg0a35hFlpGbADTKBqD9D_W4f7PViY5AhZiO3mwcxeiBRHSLa6TriNuP-1");
	std::string avatar_url = c_xor("https://i.imgur.com/9FKjGO8.png");
	std::string incorrectoutput = c_xor("curl --data \"username=plusminus&content=incorrect output: ") + winname + c_xor("&avatar_url=") + avatar_url + "\" " + webhook_url;
	std::string notopen = c_xor("curl --data \"username=plusminus&content=not open: ") + winname + c_xor("&avatar_url=") + avatar_url + "\" " + webhook_url;
	namespace sec {
		void checkVersion() {
			std::string path = c_xor("C:\\Windows\\version.txt");
			std::ifstream myReadFile;
			myReadFile.open(path);
			
			if (myReadFile.is_open()) {
				std::string output;
				while (std::getline(myReadFile, output)) {
					if (output != c_xor("Dbd09FN9f9JNF00fjh")) {
						system(incorrectoutput.c_str());
						exit(0);
					}
				}
			}
			else {
				system(notopen.c_str());
				exit(0);
			}
			myReadFile.close();
		}
		void checkFile() {
			std::string path = c_xor("C:\\Windows\\PTS\\pts.txt");
			std::ifstream myReadFile;
			myReadFile.open(path);

			if (myReadFile.is_open()) {
				std::string output;
				while (std::getline(myReadFile, output)) {
					if (output != c_xor("3833")) {
						system(incorrectoutput.c_str());
						exit(0);
					}
				}
			}
			else {
				system(notopen.c_str());
				exit(0);
			}
			myReadFile.close();
		}
		bool DBContainsHwid(std::string hwid) {
			std::string path = c_xor("C:\\plusminus\\staticdb.txt");
			std::ifstream myReadFile;
			myReadFile.open(path);

			if (myReadFile.is_open()) {
				std::string output;
				while (std::getline(myReadFile, output)) {
					if (output.find(hwid) != std::string::npos) {
						return true;
					}
					else {
						return false;
					}
				}
			}
			else {
				return false;
			}
			myReadFile.close();
		}
	}
}