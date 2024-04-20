/**
 * Sarspec Linux usb device library
 * Project Name:
 * Design Name:
 * Linux Device Driver
 * working  with kernel 5.10
 *
 * Copyright  2024-present IPFN-Instituto Superior Tecnico, Portugal
 * Creation Date  2024-04-20
 */

#ifndef SARSPEC_DEVICE_H_
#define SARSPEC_DEVICE_H_

#include <stdio.h>
#include <stdlib.h>
#include <libftdi1/ftdi.h>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>

#define DEBUG

#ifdef DEBUG
#include <time.h>
#endif

namespace sarspec_usb {

    /**
     * SARSPEC_DEVICE_H
     * @brief Sarspec device driver wrapper. Provides controllables that provide configuration and sampling functionality.
     */
    class SarspecResDevice{

        public:

            /**
             * @brief Construct the SarspecResDevice object and initialize its internal data buffer.
             * @param 
             * @param 
             *
             */
            SarspecResDevice();
            /**
             * @brief Clear 
             */
            virtual ~SarspecResDevice();


            bool connect(int vendor, int product);
            int disconnect();
            int led(bool value);

            char* readEEPROMPage(int page);
            double* getCurrentEEPROMDarkGain();

            double setDark(int dark);
            double setGain(int gain);
            bool setDeviceGain(int gain);
            bool setIntegrationTime(int intTime);
            bool setTimeout(int timeOut);

            std::vector<double> YData(bool extTrigger, int delay);
            std::vector<double> XData(double coeffs[4]);

        private:

            struct ftdi_context *ftdi;
            struct ftdi_transfer_control* tc;

            int status;

            const int P = 3648;  //Sony 2048    Toshiba 3648
            const int L = 3694;  //Sony 2087    Toshiba 3694

            uint32_t offsetTimeout = 100;
            uint32_t calcTimeOut = 0;
            uint32_t tExtDelay = 0;
            uint32_t delay_old = 0;


            std::vector<double> yData;
            std::vector<double> xData;


            double darkGain[2];
            double gain0;
            const int DA_LEVELS = 65536;
    };
}

#endif //  SARSPEC_DEVICE_H_
// vim: syntax=cpp ts=4 sw=4 sts=4 sr et

