/* Auto-generated config file hpl_port_config.h */
#ifndef HPL_PORT_CONFIG_H
#define HPL_PORT_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <e> PORT Input Event 0 configuration
// <id> enable_port_input_event_0
#ifndef CONF_PORT_EVCTRL_PORT_0
#define CONF_PORT_EVCTRL_PORT_0 0
#endif

// <h> PORT Input Event 0 configuration on PORT A

// <q> PORTA Input Event 0 Enable
// <i> The event action will be triggered on any incoming event if PORT A Input Event 0 configuration is enabled
// <id> porta_input_event_enable_0
#ifndef CONF_PORTA_EVCTRL_PORTEI_0
#define CONF_PORTA_EVCTRL_PORTEI_0 0x0
#endif

// <o> PORTA Event 0 Pin Identifier <0x00-0x1F>
// <i> These bits define the I/O pin from port A on which the event action will be performed
// <id> porta_event_pin_identifier_0
#ifndef CONF_PORTA_EVCTRL_PID_0
#define CONF_PORTA_EVCTRL_PID_0 0x0
#endif

// <o> PORTA Event 0 Action
// <0=> Output register of pin will be set to level of event
// <1=> Set output register of pin on event
// <2=> Clear output register of pin on event
// <3=> Toggle output register of pin on event
// <i> These bits define the event action the PORT A will perform on event input 0
// <id> porta_event_action_0
#ifndef CONF_PORTA_EVCTRL_EVACT_0
#define CONF_PORTA_EVCTRL_EVACT_0 0
#endif

// </h>

// </e>

// <e> PORT Input Event 1 configuration
// <id> enable_port_input_event_1
#ifndef CONF_PORT_EVCTRL_PORT_1
#define CONF_PORT_EVCTRL_PORT_1 0
#endif

// <h> PORT Input Event 1 configuration on PORT A

// <q> PORTA Input Event 1 Enable
// <i> The event action will be triggered on any incoming event if PORT A Input Event 1 configuration is enabled
// <id> porta_input_event_enable_1
#ifndef CONF_PORTA_EVCTRL_PORTEI_1
#define CONF_PORTA_EVCTRL_PORTEI_1 0x0
#endif

// <o> PORTA Event 1 Pin Identifier <0x00-0x1F>
// <i> These bits define the I/O pin from port A on which the event action will be performed
// <id> porta_event_pin_identifier_1
#ifndef CONF_PORTA_EVCTRL_PID_1
#define CONF_PORTA_EVCTRL_PID_1 0x0
#endif

// <o> PORTA Event 1 Action
// <0=> Output register of pin will be set to level of event
// <1=> Set output register of pin on event
// <2=> Clear output register of pin on event
// <3=> Toggle output register of pin on event
// <i> These bits define the event action the PORT A will perform on event input 1
// <id> porta_event_action_1
#ifndef CONF_PORTA_EVCTRL_EVACT_1
#define CONF_PORTA_EVCTRL_EVACT_1 0
#endif

// </h>

// </e>

// <e> PORT Input Event 2 configuration
// <id> enable_port_input_event_2
#ifndef CONF_PORT_EVCTRL_PORT_2
#define CONF_PORT_EVCTRL_PORT_2 0
#endif

// <h> PORT Input Event 2 configuration on PORT A

// <q> PORTA Input Event 2 Enable
// <i> The event action will be triggered on any incoming event if PORT A Input Event 2 configuration is enabled
// <id> porta_input_event_enable_2
#ifndef CONF_PORTA_EVCTRL_PORTEI_2
#define CONF_PORTA_EVCTRL_PORTEI_2 0x0
#endif

// <o> PORTA Event 2 Pin Identifier <0x00-0x1F>
// <i> These bits define the I/O pin from port A on which the event action will be performed
// <id> porta_event_pin_identifier_2
#ifndef CONF_PORTA_EVCTRL_PID_2
#define CONF_PORTA_EVCTRL_PID_2 0x0
#endif

// <o> PORTA Event 2 Action
// <0=> Output register of pin will be set to level of event
// <1=> Set output register of pin on event
// <2=> Clear output register of pin on event
// <3=> Toggle output register of pin on event
// <i> These bits define the event action the PORT A will perform on event input 2
// <id> porta_event_action_2
#ifndef CONF_PORTA_EVCTRL_EVACT_2
#define CONF_PORTA_EVCTRL_EVACT_2 0
#endif

// </h>

// </e>

// <e> PORT Input Event 3 configuration
// <id> enable_port_input_event_3
#ifndef CONF_PORT_EVCTRL_PORT_3
#define CONF_PORT_EVCTRL_PORT_3 0
#endif

// <h> PORT Input Event 3 configuration on PORT A

// <q> PORTA Input Event 3 Enable
// <i> The event action will be triggered on any incoming event if PORT A Input Event 3 configuration is enabled
// <id> porta_input_event_enable_3
#ifndef CONF_PORTA_EVCTRL_PORTEI_3
#define CONF_PORTA_EVCTRL_PORTEI_3 0x0
#endif

// <o> PORTA Event 3 Pin Identifier <0x00-0x1F>
// <i> These bits define the I/O pin from port A on which the event action will be performed
// <id> porta_event_pin_identifier_3
#ifndef CONF_PORTA_EVCTRL_PID_3
#define CONF_PORTA_EVCTRL_PID_3 0x0
#endif

// <o> PORTA Event 3 Action
// <0=> Output register of pin will be set to level of event
// <1=> Set output register of pin on event
// <2=> Clear output register of pin on event
// <3=> Toggle output register of pin on event
// <i> These bits define the event action the PORT A will perform on event input 3
// <id> porta_event_action_3
#ifndef CONF_PORTA_EVCTRL_EVACT_3
#define CONF_PORTA_EVCTRL_EVACT_3 0
#endif

// </h>

// </e>

#define CONF_PORTA_EVCTRL                                                                                              \
	(0 | PORT_EVCTRL_EVACT0(CONF_PORTA_EVCTRL_EVACT_0) | CONF_PORTA_EVCTRL_PORTEI_0 << PORT_EVCTRL_PORTEI0_Pos         \
	 | PORT_EVCTRL_PID0(CONF_PORTA_EVCTRL_PID_0) | PORT_EVCTRL_EVACT1(CONF_PORTA_EVCTRL_EVACT_1)                       \
	 | CONF_PORTA_EVCTRL_PORTEI_1 << PORT_EVCTRL_PORTEI1_Pos | PORT_EVCTRL_PID1(CONF_PORTA_EVCTRL_PID_1)               \
	 | PORT_EVCTRL_EVACT2(CONF_PORTA_EVCTRL_EVACT_2) | CONF_PORTA_EVCTRL_PORTEI_2 << PORT_EVCTRL_PORTEI2_Pos           \
	 | PORT_EVCTRL_PID2(CONF_PORTA_EVCTRL_PID_2) | PORT_EVCTRL_EVACT3(CONF_PORTA_EVCTRL_EVACT_3)                       \
	 | CONF_PORTA_EVCTRL_PORTEI_3 << PORT_EVCTRL_PORTEI3_Pos | PORT_EVCTRL_PID3(CONF_PORTA_EVCTRL_PID_3))

// <<< end of configuration section >>>

#endif // HPL_PORT_CONFIG_H
