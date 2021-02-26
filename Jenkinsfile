pipeline {
    agent {
        docker { 
            image 'ubuntu_ci:latest' 
        }
    }
    stages {
        stage('build') {
            steps {
                sh '''

                    uname -a
                    cat /etc/issue
                    apt-get update
                    apt-get install -y -qq lib32ncurses5 lib32z1 > /dev/null

                    curl -s http://download.isrc.rt-thread.com/download/gcc-arm-none-eabi-5_4-2016q3-20160926-linux.tar.bz2 | sudo tar xjf - -C /opt
                    /opt/gcc-arm-none-eabi-5_4-2016q3/bin/arm-none-eabi-gcc --version
                '''

                script {
                    def bsp_array = [
                        ['CME_M7', 'sourcery-arm'],
                        // ['apollo2', 'sourcery-arm'], /* CI compile not support */
                        ['asm9260t', 'sourcery-arm'],
                        ['at91sam9260', 'sourcery-arm'],
                        ['allwinner_tina', 'sourcery-arm'],
                        ['efm32', 'sourcery-arm'],
                        // ['gd32e230k-start', 'sourcery-arm'], /* CI compile not support */
                        ['gd32303e-eval', 'sourcery-arm'],
                        // ['gd32450z-eval', 'sourcery-arm'], /* CI link not support */
                        ['gkipc', 'sourcery-arm'],
                        ['imx6sx/cortex-a9', 'sourcery-arm'],
                        // ['imxrt/imxrt1052-atk-commander', 'sourcery-arm'], /* CI compile not support */
                        // ['imxrt/imxrt1052-fire-pro', 'sourcery-arm'], /* CI compile not support */
                        // ['imxrt/imxrt1052-nxp-evk', 'sourcery-arm'], /* CI compile not support */
                        ['lm3s8962', 'sourcery-arm'],
                        ['lm3s9b9x', 'sourcery-arm'],
                        ['lm4f232', 'sourcery-arm'],
                        ['tm4c129x', 'sourcery-arm'],
                        // ['lpc43xx/M4', 'sourcery-arm'], /* CI compile not support */
                        ['lpc176x', 'sourcery-arm'],
                        ['lpc178x', 'sourcery-arm'],
                        ['lpc408x', 'sourcery-arm'],
                        ['lpc1114', 'sourcery-arm'],
                        ['lpc2148', 'sourcery-arm'],
                        ['lpc2478', 'sourcery-arm'],
                        ['lpc5410x', 'sourcery-arm'],
                        // ['lpc54114-lite', 'sourcery-arm'], /* CI link not support */
                        ['mb9bf500r', 'sourcery-arm'],
                        ['mb9bf506r', 'sourcery-arm'],
                        ['mb9bf618s', 'sourcery-arm'],
                        ['mb9bf568r', 'sourcery-arm'],
                        ['mini2440', 'sourcery-arm'],
                        ['nuvoton_nuc472', 'sourcery-arm'],
                        ['nuvoton_m05x', 'sourcery-arm'],
                        ['qemu-vexpress-a9', 'sourcery-arm'],
                        ['qemu-vexpress-gemini', 'sourcery-arm'],
                        ['sam7x', 'sourcery-arm'],
                        // ['stm32/stm32f072-st-nucleo', 'sourcery-arm'], /* CI compile C99 not support */
                        // ['stm32/stm32f091-st-nucleo', 'sourcery-arm'], /* CI compile C99 not support */
                        // ['stm32/stm32f103-atk-nano', 'sourcery-arm'], /* CI compile C99 not support */
                        // ['stm32/stm32f103-atk-warshipv3', 'sourcery-arm'], /* CI compile C99 not support */
                        // ['stm32/stm32f103-dofly-lyc8', 'sourcery-arm'], /* CI compile C99 not support */
                        // ['stm32/stm32f103-dofly-M3S', 'sourcery-arm'], /* CI compile C99 not support */
                        // ['stm32/stm32f103-fire-arbitrary', 'sourcery-arm'], /* CI compile C99 not support */
                        // ['stm32/stm32f103-hw100k-ibox', 'sourcery-arm'], /* CI compile C99 not support */
                        // ['stm32/stm32f103-mini-system', 'sourcery-arm'], /* CI compile C99 not support */
                        // ['stm32/stm32f103-onenet-nbiot', 'sourcery-arm'], /* CI compile C99 not support */
                        // ['stm32/stm32f103-yf-ufun', 'sourcery-arm'], /* CI compile C99 not support */
                        // ['stm32/stm32f107-uc-eval', 'sourcery-arm'], /* CI compile C99 not support */
                        // ['stm32/stm32f401-st-nucleo', 'sourcery-arm'], /* CI compile C99 not support */
                        // ['stm32/stm32f405-smdz-breadfruit', 'sourcery-arm'], /* CI compile C99 not support */
                        // ['stm32/stm32f407-atk-explorer', 'sourcery-arm'], /* CI compile C99 not support */
                        // ['stm32/stm32f407-st-discovery', 'sourcery-arm'], /* CI compile C99 not support */
                        // ['stm32/stm32f410-st-nucleo', 'sourcery-arm'], /* CI compile C99 not support */
                        // ['stm32/stm32f411-st-nucleo', 'sourcery-arm'], /* CI compile C99 not support */
                        // ['stm32/stm32f411-weact-MiniF4', 'sourcery-arm'], /* CI compile C99 not support */
                        // ['stm32/stm32f413-st-nucleo', 'sourcery-arm'], /* CI compile C99 not support */
                        // ['stm32/stm32f427-robomaster-a', 'sourcery-arm'], /* CI compile C99 not support */
                        // ['stm32/stm32f429-armfly-v6', 'sourcery-arm'], /* CI compile C99 not support */
                        // ['stm32/stm32f429-atk-apollo', 'sourcery-arm'], /* CI compile C99 not support */
                        // ['stm32/stm32f429-fire-challenger', 'sourcery-arm'], /* CI compile C99 not support */
                        // ['stm32/stm32f429-st-disco', 'sourcery-arm'], /* CI compile C99 not support */
                        // ['stm32/stm32f446-st-nucleo', 'sourcery-arm'], /* CI compile C99 not support */
                        // ['stm32/stm32f469-st-disco', 'sourcery-arm'], /* CI compile C99 not support */
                        // ['stm32/stm32f746-st-disco', 'sourcery-arm'], /* CI compile -mcpu= not support */
                        // ['stm32/stm32f767-atk-apollo', 'sourcery-arm'], /* CI compile -mcpu= not support */
                        // ['stm32/stm32f767-fire-challenger', 'sourcery-arm'], /* CI compile -mcpu= not support */
                        // ['stm32/stm32f767-st-nucleo', 'sourcery-arm'], /* CI compile -mcpu= not support */
                        // ['stm32/stm32g071-st-nucleo', 'sourcery-arm'], /* CI compile C99 not support */
                        // ['stm32/stm32g431-st-nucleo', 'sourcery-arm'], /* CI compile C99 not support */
                        // ['stm32/stm32h743-atk-apollo', 'sourcery-arm'], /* CI compile -mcpu= not support */
                        // ['stm32/stm32h743-st-nucleo', 'sourcery-arm'], /* CI compile -mcpu= not support */
                        // ['stm32/stm32h747-st-discovery', 'sourcery-arm'], /* CI compile -mcpu= not support */
                        // ['stm32/stm32l4r9-st-eval', 'sourcery-arm'], /* CI compile C99 not support */
                        // ['stm32/stm32l010-st-nucleo', 'sourcery-arm'], /* CI compile C99 not support */
                        // ['stm32/stm32l053-st-nucleo', 'sourcery-arm'], /* CI compile C99 not support */
                        // ['stm32/stm32l412-st-nucleo', 'sourcery-arm'], /* CI compile C99 not support */
                        // ['stm32/stm32l432-st-nucleo', 'sourcery-arm'], /* CI compile C99 not support */
                        // ['stm32/stm32l433-st-nucleo', 'sourcery-arm'], /* CI compile C99 not support */
                        // ['stm32/stm32l475-atk-pandora', 'sourcery-arm'], /* CI compile C99 not support */
                        // ['stm32/stm32l475-st-discovery', 'sourcery-arm'], /* CI compile C99 not support */
                        // ['stm32/stm32l476-st-nucleo', 'sourcery-arm'], /* CI compile C99 not support */
                        // ['stm32/stm32l496-ali-developer', 'sourcery-arm'], /* CI compile C99 not support */
                        // ['stm32/stm32l496-st-nucleo', 'sourcery-arm'], /* CI compile C99 not support */
                        ['stm32f20x', 'sourcery-arm'],
                        ['swm320-lq100', 'sourcery-arm'],
                        ['beaglebone', 'sourcery-arm'],
                        ['zynq7000', 'sourcery-arm'],
                        ['frdm-k64f', 'sourcery-arm'],
                        ['fh8620', 'sourcery-arm'],
                        ['xplorer4330/M4', 'sourcery-arm'],
                        // ['at32/at32f403a-start', 'sourcery-arm'],/* CI link not support */
                        // ['at32/at32f407-start', 'sourcery-arm']/* CI compile C99 not support */
                    ]

                    for (int i in bsp_array) {

                        sh """

                        export RTT_BSP=${i.getAt(0)}
                        export RTT_TOOL_CHAIN=${i.getAt(1)}
                        export RTT_EXEC_PATH=/opt/gcc-arm-none-eabi-5_4-2016q3/bin/
                        export RTT_CC='gcc'
                        export RTT_ROOT=`pwd`

                        echo \$RTT_EXEC_PATH

                        export CPUS=\$(cat /proc/cpuinfo | grep "processor" | sort | uniq | wc -l)
                        scons -j\${CPUS} -C bsp/\$RTT_BSP
                        """
                    }
                }
            }
        }
    }
    post {
        failure {
            addGiteeMRComment(comment: """:x: Jenkins CI 构建失败。\n\n \
查看更多日志详细信息： \
<a href="${env.RUN_DISPLAY_URL}">Jenkins[${env.JOB_NAME} # ${env.BUILD_NUMBER}]</a> \
<hr /> \
:x: The Jenkins CI build failed.\n\n \
Results available at: \
<a href="${env.RUN_DISPLAY_URL}">Jenkins[${env.JOB_NAME} # ${env.BUILD_NUMBER}]</a>""")
        }
        success {
            addGiteeMRComment(comment: """:white_check_mark: Jenkins CI 构建通过。\n\n \
查看更多日志详细信息： \
<a href="${env.RUN_DISPLAY_URL}">Jenkins[${env.JOB_NAME} # ${env.BUILD_NUMBER}]</a> \
<hr /> \
:white_check_mark: The Jenkins CI build passed.\n\n \
Results available at: \
<a href="${env.RUN_DISPLAY_URL}">Jenkins[${env.JOB_NAME} # ${env.BUILD_NUMBER}]</a>""")
        }
    }
}
