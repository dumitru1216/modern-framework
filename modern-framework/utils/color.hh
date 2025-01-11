#pragma once

// ik its not part of math but whatever
namespace math_wraper {
	class c_color {
	public:
		c_color( ) : r( 255 ), g( 255 ), b( 255 ), a( 255 ) { }
		c_color( int r, int g, int b, int a = 255 ) : r( r ), g( g ), b( b ), a( a ) { }
		~c_color( ) { }

		int r, g, b, a;
	};
}