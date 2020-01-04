#define NUM_VNH7040PWM		4

/****************************************************************************
**	FUNCTION PROTOTYPES
****************************************************************************/

namespace Orangebot
{

//Initialize OrangeBot motor board processor
void orangebotNodeCppInit( void );
//Parse string char by char
void orangebotParse( std::string str );
//Fetch a PWM reading
int get_pwm( int channel );

} //End namespace: Orangebot
