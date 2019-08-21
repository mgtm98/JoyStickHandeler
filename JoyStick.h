#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

#include <linux/joystick.h>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>

// the code ueses a c Code to read JoyStick input file and a C++ class to easy use it later


/*        _=====_                               _=====_
         / _____ \                             / _____ \
       +.-'_____'-.---------------------------.-'_____'-.+
      /   |     |  '.                       .'  |  _  |   \
     / ___| /|\ |___ \                     / ___| /_\ |___ \
    / |      |      | ;  __           _   ; | _         _ | ;
    | | <---   ---> | | |__|         |_:> | ||_|       (_)| |
    | |___   |   ___| ;                   ; |___       ___| ;
    |\    | \|/ |    /  _     ___      _   \    | (X) |    /|
    | \   |_____|  .','" "', |___|  ,'" "', '.  |_____|  .' |
    |  '-.______.-' /       \ANALOG/       \  '-._____.-'   |
    |               |       |------|       |                |
    |              /\       /      \       /\               |
    |             /  '.___.'        '.___.'  \              |
    |            /                            \             |
     \          /                              \           /
      \________/                                \_________/    

*/

class JoyStick{

private :
    int js_D;                     // the file descriptor
    __u8 axes_count;              // number of axis in the device
    __u8 btn_count;               // number of buttons in the device
    struct js_event event;
    struct AxesState *axes;        
    int read_Event(struct js_event *event, const int descriptor);
    void get_axis_state(struct js_event *event);
    
    
public :
    JoyStick(const char *path = "/dev/input/js0");
    ~JoyStick();
    int get_axesCount() const;
    int get_btnCount() const;
    void start_Listening();
    AxesState* get_axes() const;

    virtual void axis_Event_handeler(__u32 timeStamp, __u8 number, __s16 value) const = 0;
    virtual void btn_Event_handeler(__u32 timeStamp, __u8 number, __s16 value) const = 0;
};

struct AxesState{
    short x = 0;
    short y = 0;
};

#endif