#include <boost/units/quantity.hpp> 
#include <boost/units/systems/si/plane_angle.hpp> 
#include <boost/units/systems/angle/degrees.hpp> 

#include "OpenGL.h"

GLfloat radians(GLfloat deg)
{
	return static_cast<boost::units::quantity<boost::units::si::plane_angle>>(deg * boost::units::degree::degree).value();
}

GLfloat degrees(GLfloat rad)
{
	return static_cast<boost::units::quantity<boost::units::degree::plane_angle>>(rad * boost::units::si::radians).value();
}
