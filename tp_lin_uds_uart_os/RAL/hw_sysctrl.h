/**
 *  \file  hw_sysctrl.h
 *
 *  \brief    This file contains the physical addresses of system control moodule
 *
 *  \date     Aug 6, 2017
 *  \author   Mohab Adel
 */

#ifndef HW_SYSCTRL_H_
#define HW_SYSCTRL_H_

#define BASE_SYSTEM_CONTROL 0x400FE000
/**
 * system control registers
 * */
#define DEVICE_IDENTIFICATION_0_OFFSET                                              0x000
#define DEVICE_IDENTIFICATION_1_OFFSET                                              0x004
#define BROWN_OUT_RESET_CONTROL_OFFSET                                              0x030
#define RAW_INTERRUPT_STATUS_OFFSET                                                 0x050
#define INTERRUPT_MASK_CONTROL_OFFSET                                               0x054
#define MASKED_INTERRUPT_STATUS_AND_CLEAR_OFFSET                                    0x058
#define RESET_CAUSE_OFFSET                                                          0x05C
#define RUN_MODE_CLOCK_CONFIGURATION_OFFSET                                         0x060
#define GPIO_HIGH_PERFORMANCE_BUS_CONTROL_OFFSET                                    0x06C
#define RUN_MODE_CLOCK_CONFIGURATION_2_OFFSET                                       0x070
#define MAIN_OSCILLATOR_CONTROL_OFFSET                                              0x07C
#define DEEP_SLEEP_CLOCK_CONFIGURATION_OFFSET                                       0x144
#define SYSTEM_PROPERTIES_OFFSET                                                    0x14C
#define PRECEISION_INTERNAL_OSCILLATOR_CALIBRATION_OFFSET                           0x150
#define PRECEISION_INTERNAL_OSCILLATOR_STATISTICS_OFFSET                            0x154
#define PHASE_LOCKED_LOOP_FREQUENCY_0_OFFSET                                        0x160
#define PHASE_LOCKED_LOOP_FREQUENCY_1_OFFSET                                        0x164
#define PHASE_LOCKED_LOOP_STATUS_OFFSET                                             0x168
#define SLEEP_POWER_CONFIGURATION_OFFSET                                            0x188
#define DEEP_SLEEP_POWER_CONFIGURATION_OFFSET                                       0x18C
#define LDO_SLEEP_POWER_CONTROL_OFFSET                                              0x1B4
#define LDO_SLEEP_POWER_CALIBRATION_OFFSET                                          0x1B8
#define LDO_DEEP_SLEEP_POWER_CONTROL_OFFSET                                         0x1BC
#define LDO_DEEP_SLEEP_POWER_CALIBRATION_OFFSET                                     0x1C0
#define SLEEP_DEEP_SLEEP_POWER_MODE_STATUS_OFFSET                                   0x1CC
/****************************************************************************************
 * system control peripheral present registers offsets
 ****************************************************************************************/
#define WATCHDOG_TIMER_PERIPHERAL_PRESENT                                           0x300
#define GENERAL_PURPOSE_16_32_BIT_TIMER_PERIPHERAL_PRESENT_OFFSET                   0x304
#define GPIO_PERIPHERAL_PRESENT_OFFSET                                              0x308
#define MICRO_DIRECT_MEMORY_ACCESS_PERIPHERAL_PRESENT_OFFSET                        0x30C
#define HIBERNATION_PERIPHERAL_PRESENT_OFFSET                                       0x314
#define UART_PERIPHERAL_PRESENT_OFFSET                                              0x318
#define SSI_PERIPHERAL_PRESENT_OFFSET                                               0x31C
#define I2C_PERIPHERAL_PRESENT_OFFSET                                               0x320
#define USB_PERIPHERAL_PRESENT_OFFSET                                               0x328
#define CAN_PERIPHERAL_PRESENT_OFFSET                                               0x334
#define ANALOG_COMPARATOR_PERIPHERAL_PRESENT_OFFSET                                 0x33C
#define PWM_PERIPHERAL_PRESENT_OFFSET                                               0x340
#define QEI_PERIPHERAL_PRESENT_OFFSET                                               0x344
#define EEPROM_PERIPHERAL_PRESENT_OFFSET                                            0x358
#define GENERAL_PURPOSE_32_64_TIMER_PERIPHERAL_PRESENT_OFFSET                       0x35C
/****************************************************************************************
 * system control software reset registers offsets
 ****************************************************************************************/
#define WATCHDOG_TIMER_SOFTWARE_RESET_OFFSET                                        0x500
#define GENERAL_PURPOSE_16_32_BIT_TIMER_SOFTWARE_RESET_OFFSET                       0x504
#define GENERAL_PURPOSE_INPUT_OUTPUT_SOFTWARE_RESET_OFFSET                          0x508
#define MICRO_DIRECT_MEMORY_ACCESS_SOFTWARE_RESET_OFFSET                            0x50C
#define HIBERNATION_SOFTWARE_RESET_OFFSET                                           0x514
#define UART_SOFTWARE_RESET_OFFSET                                                  0x518
#define SSI_SOFTWARE_RESET_OFFSET                                                   0x51C
#define I2C_SOFTWARE_RESET_OFFSET                                                   0x520
#define USB_SOFTWARE_RESET_OFFSET                                                   0x528
#define CAN_SOFTWARE_RESET_OFFSET                                                   0x534
#define ADC_SOFTWARE_RESET_OFFSET                                                   0x538
#define ANALOG_COMPARATOR_SOFTWARE_RESET_OFFSET                                     0x53C
#define PWM_SOFTWARE_RESET_OFFSET                                                   0x540
#define QEI_SOFTWARE_RESET_OFFSET                                                   0x544
#define EEPROM_SOFTWARE_RESET_OFFSET                                                0x558
#define GENERAL_PURPOSE_32_64_BIT_TIMER_SOFTWARE_RESET_OFFSET                       0x55C
/****************************************************************************************
 * system control run mode clock gating control registers offsets
 ****************************************************************************************/
#define WATCHDOG_TIMER_RUN_MODE_CLOCK_GATING_CONTROL_OFFSET                         0x600
#define GENERAL_PURPOSE_16_32_BIT_TIMER_RUN_MODE_CLOCK_GATING_CONTROL_OFFSET        0x604
#define GPIO_RUN_MODE_CLOCK_GATING_CONTROL_OFFSET                                   0x608
#define MICRO_DIRECT_MEMORY_ACCESS_RUN_MODE_CLOCK_GATING_CONTROL_OFFSET             0x60C
#define HIBERNATION_RUN_MODE_CLOCK_GATING_CONTROL_OFFSET                            0x614
#define UART_RUN_MODE_CLOCK_GATING_CONTROL_OFFSET                                   0x618
#define SSI_RUN_MODE_CLOCK_GATING_CONTROL_OFFSET                                    0x61C
#define I2C_RUN_MODE_CLOCK_GATING_CONTROL_OFFSET                                    0x620
#define USB_RUN_MODE_CLOCK_GATING_CONTROL_OFFSET                                    0x628
#define CAN_RUN_MODE_CLOCK_GATING_CONTROL_OFFSET                                    0x634
#define ADC_RUN_MODE_CLOCK_GATING_CONTROL_OFFSET                                    0x638
#define ANALOG_COMPARATOR_RUN_MODE_CLOCK_GATING_CONTROL_OFFSET                      0x63C
#define PWM_RUN_MODE_CLOCK_GATING_CONTROL_OFFSET                                    0x640
#define QEI_RUN_MODE_CLOCK_GATING_CONTROL_OFFSET                                    0x644
#define EEPROM_RUN_MODE_CLOCK_GATING_CONTROL_OFFSET                                 0x658
#define GENERAL_PURPOSE_32_64_BIT_TIMER_RUN_MODE_CLOCK_GATING_CONTROL_OFFSET        0x65C
/****************************************************************************************
 * system control sleep mode clock gating control registers offsets
 ****************************************************************************************/
#define WATCHDOG_TIMER_SLEEP_MODE_CLOCK_GATING_CONTROL_OFFSET                       0x700
#define GENERAL_PURPOSE_16_32_BIT_TIMER_SLEEP_MODE_CLOCK_GATING_CONTROL_OFFSET      0x704
#define GPIO_SLEEP_MODE_CLOCK_GATING_CONTROL_OFFSET         0x708
#define MICRO_DIRECT_MEMORY_ACCESS_SLEEP_MODE_CLOCK_GATING_CONTROL_OFFSET           0x70C
#define HIBERNATION_SLEEP_MODE_CLOCK_GATING_CONTROL_OFFSET                          0x714
#define UART_SLEEP_MODE_CLOCK_GATING_CONTROL_OFFSET                                 0x718
#define SSI_SLEEP_MODE_CLOCK_GATING_CONTROL_OFFSET                                  0x71C
#define I2C_SLEEP_MODE_CLOCK_GATING_CONTROL_OFFSET                                  0x720
#define USB_SLEEP_MODE_CLOCK_GATING_CONTROL_OFFSET                                  0x728
#define CAN_SLEEP_MODE_CLOCK_GATING_CONTROL_OFFSET                                  0x734
#define ADC_SLEEP_MODE_CLOCK_GATING_CONTROL_OFFSET                                  0x738
#define ANALOG_COMPARATOR_SLEEP_MODE_CLOCK_GATING_CONTROL_OFFSET                    0x73C
#define PWM_SLEEP_MODE_CLOCK_GATING_CONTROL_OFFSET                                  0x740
#define QEI_SLEEP_MODE_CLOCK_GATING_CONTROL_OFFSET                                  0x744
#define EEPROM_SLEEP_MODE_CLOCK_GATING_CONTROL_OFFSET                               0x758
#define GENERAL_PURPOSE_32_64_BIT_TIMER_SLEEP_MODE_CLOCK_GATING_CONTROL_OFFSET      0x75C
/****************************************************************************************
 * system control deep sleep mode clock gating control registers offsets
 ****************************************************************************************/
#define WATCHDOG_TIMER_DEEP_SLEEP_MODE_CLOCK_GATING_CONTROL_OFFSET                  0x800
#define GENERAL_PURPOSE_16_32_BIT_TIMER_DEEP_SLEEP_MODE_CLOCK_GATING_CONTROL_OFFSET 0x804
#define GPIO_DEEP_SLEEP_MODE_CLOCK_GATING_CONTROL_OFFSET    0x808
#define MICRO_DIRECT_MEMORY_ACCESS_DEEP_SLEEP_MODE_CLOCK_GATING_CONTROL_OFFSET      0x80C
#define HIBERNATION_DEEP_SLEEP_MODE_CLOCK_GATING_CONTROL_OFFSET                     0x814
#define UART_DEEP_SLEEP_MODE_CLOCK_GATING_CONTROL_OFFSET                            0x818
#define SSI_DEEP_SLEEP_MODE_CLOCK_GATING_CONTROL_OFFSET                             0x81C
#define I2C_DEEP_SLEEP_MODE_CLOCK_GATING_CONTROL_OFFSET                             0x820
#define USB_DEEP_SLEEP_MODE_CLOCK_GATING_CONTROL_OFFSET                             0x828
#define CAN_DEEP_SLEEP_MODE_CLOCK_GATING_CONTROL_OFFSET                             0x834
#define ADC_DEEP_SLEEP_MODE_CLOCK_GATING_CONTROL_OFFSET                             0x838
#define ANALOG_COMPARATOR_DEEP_SLEEP_MODE_CLOCK_GATING_CONTROL_OFFSET               0x83C
#define PWM_DEEP_SLEEP_MODE_CLOCK_GATING_CONTROL_OFFSET                             0x840
#define QEI_DEEP_SLEEP_MODE_CLOCK_GATING_CONTROL_OFFSET                             0x844
#define EEPROM_DEEP_SLEEP_MODE_CLOCK_GATING_CONTROL_OFFSET                          0x858
#define GENERAL_PURPOSE_32_64_BIT_TIMER_DEEP_SLEEP_MODE_CLOCK_GATING_CONTROL_OFFSET 0x85C
/****************************************************************************************
 * system control peripheral ready registers offsets
 ****************************************************************************************/
#define WATCHDOG_TIMER_PERIPHERAL_READY_OFFSET                                      0xA00
#define GENERAL_PURPOSE_16_32_BIT_TIMER_PERIPHERAL_READY_OFFSET                     0xA04
#define GPIO_PERIPHERAL_READY_OFFSET                        0xA08
#define MICRO_DIRECT_MEMORY_ACCESS_PERIPHERAL_READY_OFFSET                          0xA0C
#define HIBERNATION_PERIPHERAL_READY_OFFSET                                         0xA14
#define UART_PERIPHERAL_READY_OFFSET                                                0xA18
#define SSI_PERIPHERAL_READY_OFFSET                                                 0xA1C
#define I2C_PERIPHERAL_READY_OFFSET                                                 0xA20
#define USB_PERIPHERAL_READY_OFFSET                                                 0xA28
#define CAN_PERIPHERAL_READY_OFFSET                                                 0xA34
#define ADC_PERIPHERAL_READY_OFFSET                                                 0xA38
#define ANALOG_COMPARATOR_PERIPHERAL_READY_OFFSET                                   0xA3C
#define PWM_PERIPHERAL_READY_OFFSET                                                 0xA40
#define QEI_PERIPHERAL_READY_OFFSET                                                 0xA44
#define EEPROM_PERIPHERAL_READY_OFFSET                                              0xA58
#define GENERAL_PURPOSE_32_64_BIT_TIMER_PERIPHERAL_READY_OFFSET                     0xA5C
/****************************************************************************************
 * system control legacy registers offsets
 ****************************************************************************************/

/* ====================================================================================== */
/*                                      NVIC registers                                    */
/* ====================================================================================== */
#define INTERRUPT_0_31_SET_ENABLE   	  0xE000E100
#define INTERRUPT_32_63_SET_ENABLE   	  0xE000E104
#define INTERRUPT_64_95_SET_ENABLE   	  0xE000E108
#define INTERRUPT_96_127_SET_ENABLE   	  0xE000E10C
#define INTERRUPT_128_138_SET_ENABLE   	  0xE000E110

#define INTERRUPT_0_31_CLEAR_ENABLE   	  0xE000E180
#define INTERRUPT_32_63_CLEAR_ENABLE 	  0xE000E184
#define INTERRUPT_64_95_CLEAR_ENABLE  	  0xE000E188
#define INTERRUPT_96_127_CLEAR_ENABLE     0xE000E18C
#define INTERRUPT_128_138_CLEAR_ENABLE    0xE000E190

#define INTERRUPT_0_31_SET_PENDING        0xE000E200
#define INTERRUPT_32_63_SET_PENDING       0xE000E204
#define INTERRUPT_64_95_SET_PENDING       0xE000E208
#define INTERRUPT_96_127_SET_PENDING      0xE000E20C
#define INTERRUPT_128_138_SET_PENDING     0xE000E210

#define INTERRUPT_0_31_CLEAR_PENDING      0xE000E280
#define INTERRUPT_32_63_CLEAR_PENDING     0xE000E284
#define INTERRUPT_64_95_CLEAR_PENDING     0xE000E288
#define INTERRUPT_96_127_CLEAR_PENDING    0xE000E28C
#define INTERRUPT_128_138_CLEAR_PENDING     0xE000E290

/*Interrupt active bits not listed here*/

#define INTERRUPT_0_3_PRIORITY            0xE000E400
#define INTERRUPT_4_7_PRIORITY            0xE000E404
#define INTERRUPT_8_11_PRIORITY    		  0xE000E408
#define INTERRUPT_12_15_PRIORITY     	  0xE000E40C
#define INTERRUPT_16_19_PRIORITY      	  0xE000E410
#define INTERRUPT_20_23_PRIORITY      	  0xE000E414
#define INTERRUPT_24_27_PRIORITY      	  0xE000E418
#define INTERRUPT_28_31_PRIORITY      	  0xE000E41C
#define INTERRUPT_32_35_PRIORITY      	  0xE000E420
#define INTERRUPT_36_39_PRIORITY      	  0xE000E424
#define INTERRUPT_40_43_PRIORITY      	  0xE000E428
#define INTERRUPT_44_47_PRIORITY      	  0xE000E42C
#define INTERRUPT_48_51_PRIORITY      	  0xE000E430
#define INTERRUPT_52_55_PRIORITY      	  0xE000E434
#define INTERRUPT_56_59_PRIORITY      	  0xE000E438
#define INTERRUPT_60_63_PRIORITY      	  0xE000E43C
#define INTERRUPT_64_67_PRIORITY      	  0xE000E440
#define INTERRUPT_68_71_PRIORITY      	  0xE000E444
#define INTERRUPT_72_75_PRIORITY      	  0xE000E448
#define INTERRUPT_76_79_PRIORITY      	  0xE000E44C
#define INTERRUPT_80_83_PRIORITY      	  0xE000E450
#define INTERRUPT_84_87_PRIORITY     	  0xE000E454
#define INTERRUPT_88_91_PRIORITY     	  0xE000E458
#define INTERRUPT_92_95_PRIORITY          0xE000E45C
#define INTERRUPT_96_99_PRIORITY          0xE000E460
#define INTERRUPT_100_103_PRIORITY        0xE000E464
#define INTERRUPT_104_107_PRIORITY        0xE000E468
#define INTERRUPT_108_111_PRIORITY        0xE000E46C
#define INTERRUPT_112_115_PRIORITY        0xE000E470
#define INTERRUPT_116_119_PRIORITY        0xE000E474
#define INTERRUPT_120_123_PRIORITY        0xE000E478
#define INTERRUPT_124_127_PRIORITY        0xE000E47C
#define INTERRUPT_128_131_PRIORITY        0xE000E480
#define INTERRUPT_132_135_PRIORITY        0xE000E484
#define INTERRUPT_136_138_PRIORITY        0xE000E488

#define SOFTWARE_TRIGGER_INTERRUPT        0xE000EF00

#endif /* HW_SYSTEM_CONTROL_H_ */
