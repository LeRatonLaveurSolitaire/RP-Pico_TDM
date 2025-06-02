#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define num_mics 16
#define Bits_per_mics 32

int main() {
    // Common PWM configuration
    pwm_config config = pwm_get_default_config();
    pwm_config_set_phase_correct(&config, false);
    pwm_config_set_clkdiv(&config, 1.0f);


    // Configure PWM for pin 1 (existing setup)
    gpio_set_function(1, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(1);
    pwm_set_clkdiv(slice_num, 1.0);
    pwm_set_wrap(slice_num, 125 - 1); 
    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(1), 125/2); // 50% duty
    

    gpio_set_function(2, GPIO_FUNC_PWM);
    uint slice_num2 = pwm_gpio_to_slice_num(2);
    pwm_set_clkdiv(slice_num2, 1.0);
    pwm_set_wrap(slice_num2, (125 - 1) +  125 * ( num_mics * Bits_per_mics - 1)); 
    pwm_set_chan_level(slice_num2, pwm_gpio_to_channel(2), 125/2); // 50% duty

    // Atomic start of both slices
    uint32_t mask = (1 << slice_num) | (1 << slice_num2);
    pwm_set_mask_enabled(mask);

    while(1);
}
