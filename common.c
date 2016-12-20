/*
Owner = Antonescu Radu-Ion
Year = 2016

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "common.h"

static int get_num_digits(int i, int base)
{
    int ndigit = 0;
    while (i > 0) {
        i /= base;
        ndigit++;
    }
    return ndigit;
}

void itoa(int i, char *buf, int base)
{
    int pos, num_digits = get_num_digits(i, base);
    if (num_digits == 0) {
        strcpy(buf, "0");
        return;
    }
    pos = num_digits - 1;
    while (pos >= 0) {
        buf[pos] = (i % base);
        if (buf[pos] < 10) {
            buf[pos] += '0';
        } else {
            buf[pos] += 'a' - 10;
        }
        pos--;
        i = i / base;
    }
    buf[num_digits] = '\0';
}

char* strchr(char *str, int ch)
{
    char *str_it;
    for (str_it = str; str_it != '\0'; str_it++) {
        if (*str_it == ch) return str_it;
    }
    return NULL;
}

int strcmp(const char *str1, const char *str2)
{
    while (*str1 && *str2) {
        if (*str1 < *str2) {
            return -1;
        } else if (*str1 > *str2) {
            return 1;
        }
        str1++; str2++;
    }
    if ('\0' == *str1 && '\0' == *str2) {
        return 0;
    }
    if (*str1) return 1;
    return -1;
}

int strncmp(const char *str1, const char *str2, size_t len)
{
    while (*str1 && *str2 && len > 0) {
        if (*str1 < *str2) {
            return -1;
        } else if (*str1 > *str2) {
            return 1;
        }
        str1++; str2++; len--;
    }
    if (0 == len) return 0;
    if ('\0' == *str1 && '\0' == *str2) {
        return 0;
    }
    if (*str1) return 1;
    return -1;
}

int strlen(const char *str)
{
    int len = 0;
    while(str[len] != '\0') len++;
    return len;
}

