#ifndef TOS_LOADER_H_
#define TOS_LOADER_H_

#include <string>

namespace ns3 {


class TosLoader {
	public:
		TosLoader();
		virtual
		~TosLoader();

		/**
		 * returns pointer to lib-handler
		 */
		void *
		getHandler(std::string libname);
		/**
		 * Returns pointer to tos library function
		 * For now its predefined
		 */
		void *
		getFunction(const char * func);

	private:

		/**
		 * library handler
		 */
		void *handler;
		/**
		 * Error variable, used then opening library
		 */
		char *error;

};

}

#endif /* __TOS_LOADER_H__ */

