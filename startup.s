#Owner = Antonescu Radu-Ion
#Year = 2016

#THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

.syntax unified
.global main

.section .vectors

reset:
.word start_sp
.word _start+1       @ start point
.word default_handler   @ NMI
.word _hard_fault    @ hard-fault
.word _mem_manage    @ mem-manage
.word _buf_fault     @ bus-fault
.word _usage_fault   @ usage-fault
.word 0
.word 0
.word 0
.word 0
.word default_handler   @ SVC-handler
.word default_handler   @ debug-monitor
.word 0
.word default_handler+1 @ pend-SV
.word sys_tick_handler  @ sys-tick
.word default_handler   @ watchdog
.word default_handler   @ PVD
.word default_handler   @ TAMP STAMP
.word default_handler   @ RTC Wkup
.word default_handler   @ Flash
.word default_handler   @ EINT0
.word default_handler   @ EINT1
.word default_handler   @ EINT2
.word default_handler   @ EINT3
.word default_handler   @ EINT4
.word default_handler   @ DMA0
.word default_handler   @ DMA1
.word default_handler   @ DMA2
.word default_handler   @ DMA3
.word default_handler   @ DMA4
.word default_handler   @ DMA5
.word default_handler   @ DMA6
.word default_handler   @ DMA7
.word default_handler   @ ADC
.word default_handler   @ CAN1 TX
.word default_handler   @ CAN1 RX0
.word default_handler   @ CAN1 RX1
.word default_handler   @ CAN1 SCE
.word default_handler   @ EXTI 9-5
.word default_handler   @ TIM1 BREAK TIM9
.word default_handler   @ TIM1 UP TIM10
.word default_handler   @ TIM1 TRG COM TIM11
.word default_handler   @ TIM1 CC
.word sys_tick_handler  @ TIM2
.word default_handler   @ TIM3
.word default_handler   @ TIM4
.word default_handler   @ I2C1 EV
.word default_handler   @ I2C1 ER
.word default_handler   @ I2C2 EV
.word default_handler   @ I2C2 ER
.word default_handler   @ SPI1
.word default_handler   @ SPI2
.word uart_handler      @ uart 1
.word uart_handler      @ uart 2
.word uart_handler      @ uart 3
.word default_handler   @ EXTI 15
.word default_handler   @ RTC Alarm
.word default_handler   @ OTG FS WKUP * 42
.word 0
.word 0
.word 0
.word 0
.word 0
.word 0
.word default_handler  @ TIM5
.word default_handler  @ SPI3
.word default_handler  @ UART4
.word default_handler  @ UART5
.word default_handler  @ TIM6
.word default_handler  @ TIM7
.word default_handler  @ DMA CH1
.word default_handler  @ DMA CH2
.word default_handler  @ DMA CH3
.word default_handler  @ DMA CH4
.word default_handler  @ DMA CH5

.text

_start:
    ldr sp, =start_sp

    ldr r2, =bss_size
    cmp r2, #0
    beq copy_data
    mov r0, #0
    ldr r1, =sbss

setzero:
    str.w r0, [r1], #4
    subs r2, r2, #4
    bne setzero

copy_data:
    ldr r0, =flash_data
    ldr r1, =ram_sdata
    ldr r2, =data_size
copy_data_loop:
    ldr.w r4, [r0], #4
    str.w r4, [r1], #4
    subs r2, r2, #4
    bne copy_data_loop

    b main    

