#include <string>
#include <iostream>
#include <algorithm>
#include <execution>
#include <fmt/format.h>
#include <type_traits>

#ifndef POLICY
#error "we needs a policy"
#endif

int main( int argc, char** argv ) {

	const auto f = []( const char& c ){ std::cout << c;  };
	const std::string s = fmt::format( "{}\n", "parallelo, world!" );

	for( size_t i = 0; i < 100000; i ++ ) {
		std::for_each(
				//std::execution::seq
				//std::execution::unseq
				//std::execution::par_unseq
				//std::execution::par
				POLICY
				, std::begin( s )
				, std::end( s )
				, f
				);
	}

	std::cout << std::endl << std::flush;

	return 0;
	(void) argc;
	(void) argv;
}

