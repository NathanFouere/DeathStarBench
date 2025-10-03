#ifndef SOCIAL_NETWORK_MICROSERVICES_TESTHANDLER_H
#define SOCIAL_NETWORK_MICROSERVICES_TESTHANDLER_H

#include <string>
#include "../../gen-cpp/TestService.h"

namespace social_network {
    class TestHandler: public TestServiceIf {
        public:
            TestHandler();
			void TestFunction(std::string& _return);
    };

    TestHandler::TestHandler() {
    }

	void TestHandler::TestFunction(std::string& _return) {
		_return = "Bonjour";
	}
}

#endif