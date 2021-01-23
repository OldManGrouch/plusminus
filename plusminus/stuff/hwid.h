#include <vector>
namespace hwid {
	std::vector<std::string> list = { 
		c_xor("{dc931070-657d-4be4-9f14-630684586d28}") , 
		c_xor("{15936d6f-f57a-11ea-8b4a-806e6f6e6963}") , // Morango
		c_xor("{4aafc28b-5ce9-11eb-8a83-806e6f6e6963}") , // mayoo_
		c_xor("{Apple16433-27459-31356-68921218}") , // Snowwy
		c_xor("{536c6940-008b-11eb-9275-806e6f6e6963}") , // Noah 
		c_xor("{1b7803eb-da69-11ea-a112-VmXJLbfL2MXp}") , // Gytis
		c_xor("{4b78fac3-1634-11eb-ba55-806e6f6e6963}") , // sent
		c_xor("{04de4113-b270-11ea-bf8a-806e6f6e6963}") , // Willy
		c_xor("{ec4c96f2-4ff3-11eb-8f02-806e6f6e6963}") , // Lukas Andrulis!
		c_xor("{1e038f69-2ac3-11eb-b6d7-806e6f6e6963}") , // Reese
		c_xor("{Apple12640-29747-31624-225401325}") , // bholl
		c_xor("{e949c641-48b5-11eb-825e-806e6f6e6963}") ,
		c_xor("{b32e2340-29ef-11eb-b449-806e6f6e6963}") , // kakje
		c_xor("{f79de240-0082-11eb-85f1-806e6f6e6963}") , // SAJACK
		c_xor("{e0ec89c0-2a3a-11eb-ba6e-806e6f6e6963}") , // arego 
		c_xor("{aef3b484-2d63-11eb-8e22-806e6f6e6963}") , // evans 
		c_xor("{2dba80c0-00da-11eb-b0f4-806e6f6e6963}") , // Mornz
		c_xor("{2bdfe3b4-4862-11eb-b3fe-806e6f6e6963}") , // paul 
		c_xor("{PizzaXYZ-8804-14614-22219-29502}") , // blood
		c_xor("{aff77fe6-3dc5-11eb-8084-806e6f6e6963}") , // X1
		c_xor("{5ebf94c0-008b-11eb-b602-806e6f6e6963}") , // Maxim Post
		c_xor("{a5a59008-2d3e-11eb-a9f5-806e6f6e6963}") , // dillan
		c_xor("{ff697771-de30-4e46-902e-187fea803201}") , // andru
		c_xor("{0c833340-bee3-11ea-9de1-806e6f6e6963}") , // emanu
		c_xor("{72cceaa5-b412-46bc-b276-1b1906420523}") , // Charis
		c_xor("{2a6080c0-472d-11eb-995c-806e6f6e6963}") , // shana
		c_xor("{Apple8630-18857-9853-3095421017}") , // camre
		c_xor("{Apple15611-25076-25935-2133929717}") , // Nick
		c_xor("{2c78a614-4266-11eb-b41d-806e6f6e6963}") ,
		c_xor("{91d13540-29f7-11eb-aba3-806e6f6e6963}") ,
		c_xor("{6fca8781-d0b8-11ea-b354-806e6f6e6963}") , // DREIK ON HIs fucking shadow pc
		c_xor("{5b3ac3fe-7892-11ea-e633-806e6f6e65b3}") ,
		c_xor("{5c5b05c0-3d71-11eb-9a4c-806e6f6e6963}") ,
		c_xor("{7032fb10-5e07-11eb-9f57-806e6f6e6963}") ,
		c_xor("{beba3940-0093-11eb-8bf8-806e6f6e6963}") ,
		c_xor("{0e860a29-255e-11eb-a285-806e6f6e6963}") ,
		c_xor("{c9143c92-3c1c-11eb-a701-806e6f6e6963}") ,
		c_xor("{7032fb10-5e07-11eb-9f57-806e6f6e6963}")
	};
	namespace sec {
		bool DBContainsHwid(std::string hwid) {
			return std::find(list.begin(), list.end(), hwid) != list.end();
		}
	}
}