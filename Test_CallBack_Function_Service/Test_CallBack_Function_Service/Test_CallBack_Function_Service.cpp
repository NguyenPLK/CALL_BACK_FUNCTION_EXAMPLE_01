#include <iostream>
#include <functional>
#include <vector>

struct stateChanged {
	bool recieveConnected{true};
	bool turnDownOEM{false};
};

struct callOutServiceInfo {
	stateChanged m_stateChanged;
	bool _handleStatus;
};

typedef std::function<void(callOutServiceInfo&)> ConnectedService;
//typedef int* INT;

void onConnectedServiceStateChanged(callOutServiceInfo &info) {
	auto data_recieveConnected = info.m_stateChanged.recieveConnected;
	auto data_turnDownOEM = info.m_stateChanged.turnDownOEM;
	std::cout << "data_recieveConnected: " << std::boolalpha << data_recieveConnected << std::endl;
	std::cout << "data_turnDownOEM: " << std::boolalpha << data_turnDownOEM << std::endl;
}

int main() {
	callOutServiceInfo connectedServiceInfo;
	connectedServiceInfo._handleStatus = true;
	ConnectedService registerCallBack = std::bind(&onConnectedServiceStateChanged,std::placeholders::_1);
	
	std::vector<ConnectedService*> _list_ConnectedServiceInfo;
	_list_ConnectedServiceInfo.push_back(&registerCallBack);

	for (auto it : _list_ConnectedServiceInfo) {
		callOutServiceInfo m_info;
		m_info.m_stateChanged.recieveConnected = false;
		(*it)(m_info);
	}

	//std::vector<INT*> myInt;
	//int nguyenNe = 5;
	//int* ptr = &nguyenNe;
	//myInt.push_back(&ptr);

	//for (auto it : myInt) {
	//	std::cout << *it << std::endl;
	//}

	//std::cout << &nguyenNe << std::endl;

	return 0;
}