#ifndef SYSTICK_H
#define SYSTICK_H

hw_timer_t *systickTimer = nullptr;
portMUX_TYPE systickMux = portMUX_INITIALIZER_UNLOCKED;

class Systick {
public:
    // Initialize the timer
    void begin(uint32_t interval_us = 2000) {  // default 2 ms
        // create hardware timer 0, prescaler 80 (1 tick = 1 us)
        systickTimer = timerBegin(0, 80, true); 
        // attach the interrupt to call Systick::ISR_Handler
        timerAttachInterrupt(systickTimer, &Systick::ISR_Handler, true);
        // set alarm to interval_us, autoreload
        timerAlarmWrite(systickTimer, interval_us, true);
        timerAlarmEnable(systickTimer); // start the timer
    }

    // This function will be called every tick (2 ms)
    void update() {
        portENTER_CRITICAL_ISR(&systickMux);

//HERE ENTER THE FXNS TO CALL AFTER FIXED INTERVALS

        portEXIT_CRITICAL_ISR(&systickMux);
    }

    // Static ISR wrapper
    static void IRAM_ATTR ISR_Handler() {
        if (systickInstance) systickInstance->update();
    }

    // singleton instance to call in ISR
    static Systick *systickInstance;
};

// define the singleton instance
Systick* Systick::systickInstance = nullptr;

// define extern for including in other files
extern Systick systick;

#endif
