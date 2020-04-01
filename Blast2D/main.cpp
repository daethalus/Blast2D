#include <iostream>
#include <logging/easylogging++.h>

INITIALIZE_EASYLOGGINGPP

int main() {
	LOG(INFO) << "Starting engine";
}