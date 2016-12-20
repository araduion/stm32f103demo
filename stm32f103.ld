/*
Owner = Antonescu Radu-Ion
Year = 2016

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

SECTIONS {
    . = 0x08000000;
    vector_start = .;
    .text : { startup.o (.vectors); }
    vector_end = .;
    .text : { * (.text); }
    .rodata : { * (.rodata); }
    flash_data = .;
    . = 0x20000000;
    ram_sdata = .;
    .data : AT (flash_data) { * (.data) }
    ram_edata = ALIGN(4);
    . = ram_edata;
    data_size = ram_edata - ram_sdata;
    sbss = .;
    .bss : { * (.bss); }
    ebss = ALIGN(4);
    . = ebss;
    bss_size = ebss -sbss;
    . = 0x20004FFF;
    emain_ram = .; /* end of RAM 20k */
    start_sp = emain_ram + 1; /* decrement and use style */
}

