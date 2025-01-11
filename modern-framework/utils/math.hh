#pragma once

namespace math_wraper {
	class c_vector_2d {
	public:
		// constructors
		c_vector_2d( ) : x( 0 ), y( 0 ) { }
		c_vector_2d( float x, float y ) : x( x ), y( y ) { }
		~c_vector_2d( ) { }
		
		// operators
		bool operator==( const c_vector_2d& src ) const {
			return ( src.x == this->x ) && ( src.y == y );
		}

		bool operator!=( const c_vector_2d& src ) const {
			return ( src.x != this->x ) || ( src.y != y );
		}

		float& operator[]( int i ) {
			return ( ( float* )this )[ i ];
		}

		float operator[]( int i ) const {
			return ( ( float* )this )[ i ];
		}

		c_vector_2d& operator+=( const c_vector_2d& v ) {
			this->x += v.x; this->y += v.y;
			return *this;
		}

		c_vector_2d& operator-=( const c_vector_2d& v ) {
			this->x -= v.x; this->y -= v.y;
			return *this;
		}

		c_vector_2d& operator*=( float fl ) {
			this->x *= fl;
			this->y *= fl;

			return *this;
		}

		c_vector_2d& operator*=( const c_vector_2d& v ) {
			this->x *= v.x;
			this->y *= v.y;

			return *this;
		}

		c_vector_2d& operator/=( const c_vector_2d& v ) {
			this->x /= v.x;
			this->y /= v.y;

			return *this;
		}

		c_vector_2d& operator+=( float fl ) {
			this->x += fl;
			this->y += fl;

			return *this;
		}

		c_vector_2d& operator/=( float fl ) {
			this->x /= fl;
			this->y /= fl;

			return *this;
		}

		c_vector_2d& operator-=( float fl ) {
			this->x -= fl;
			this->y -= fl;

			return *this;
		}

		c_vector_2d& operator+( c_vector_2d v ) {
			c_vector_2d temp;
			temp.x = this->x + v.x;
			temp.y = this->y + v.y;

			return temp;
		}

		c_vector_2d& operator*( c_vector_2d v ) {
			c_vector_2d temp;
			temp.x = this->x * v.x;
			temp.y = this->y * v.y;

			return temp;
		}

		c_vector_2d& operator*( float v ) {
			c_vector_2d temp;
			temp.x = this->x * v;
			temp.y = this->y * v;

			return temp;
		}

		c_vector_2d& operator-( c_vector_2d v ) {
			c_vector_2d temp;
			temp.x = this->x - v.x;
			temp.y = this->y - v.y;

			return temp;
		}

		c_vector_2d& operator/( c_vector_2d v ) {
			c_vector_2d temp;
			temp.x = this->x / v.x;
			temp.y = this->y / v.y;

			return temp;
		}

		c_vector_2d& operator/( float v ) {
			c_vector_2d temp;
			temp.x = this->x / v;
			temp.y = this->y / v;

			return temp;
		}

		// functions
		ImVec2 transform( ) {
			return ImVec2( this->x, this->y );
		}

		// vars
		int x, y;
	};
}