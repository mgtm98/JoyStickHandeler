#include "JoyStick.h"

JoyStick::JoyStick(const char *path){
    js_D = open(path, O_RDONLY);
    if(js_D == -1)
        perror("Could not open joystick");
    
    if(ioctl(js_D, JSIOCGAXES, &axes_count) == -1)axes_count = 0;
    if(ioctl(js_D, JSIOCGBUTTONS, &btn_count) == -1)btn_count = 0;
    axes = new AxesState[(int)axes_count / 2]; 
}

JoyStick::~JoyStick(){
    delete [] axes;
    close(js_D);
}

int JoyStick::get_axesCount() const{
    return axes_count;
}

int JoyStick::get_btnCount() const{
    return btn_count;
}

int JoyStick::read_Event(struct js_event *event, const int descriptor){
    ssize_t event_size ;
    event_size = read(descriptor, event, sizeof(event));
    return event_size == sizeof(event) ;
}

void JoyStick::start_Listening(){
    while(read_Event(&event,js_D)){
        switch (event.type){
        case JS_EVENT_BUTTON:
            btn_Event_handeler(event.time, event.number, event.value);
            break;
        case JS_EVENT_AXIS:
            get_axis_state(&event);
            break;
        case JS_EVENT_INIT:
            //std::cout << "INIT event" << std::endl; 
            break;    
        }
    }
}

void JoyStick::get_axis_state(struct js_event *event){
    __u8 number = event->number;
    if(number % 2 == 0){
        axes[number/2].x = event->value;
    }else{
        axes[number/2].y = event->value;
    }
    axis_Event_handeler(event->time, number, event->value);
}

AxesState* JoyStick::get_axes() const {
    return axes;
}