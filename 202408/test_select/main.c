#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/select.h>
#include <errno.h>
#include <string.h>

int main() {
    int serial_fd;
    struct termios tty;
    fd_set writefds;
    struct timeval timeout;
    const char *serial_port = "/dev/ttyS0";  // Adjust this for your system
    const char *data_to_send = "This is a very large amount of data..."; // Large data string
    size_t data_length = strlen(data_to_send);
    size_t total_written = 0;
    ssize_t bytes_written;
    
    // Open the serial port
    serial_fd = open(serial_port, O_RDWR | O_NOCTTY | O_NDELAY);
    if (serial_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Configure the serial port
    if (tcgetattr(serial_fd, &tty) < 0) {
        perror("tcgetattr");
        close(serial_fd);
        exit(EXIT_FAILURE);
    }
    cfsetispeed(&tty, B9600);
    cfsetospeed(&tty, B9600);
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~CRTSCTS;
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    tty.c_oflag &= ~OPOST;
    if (tcsetattr(serial_fd, TCSANOW, &tty) < 0) {
        perror("tcsetattr");
        close(serial_fd);
        exit(EXIT_FAILURE);
    }

    // Set up fd_set for writing
    FD_ZERO(&writefds);
    FD_SET(serial_fd, &writefds);

    // Set timeout to 5 seconds
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;

    // Wait for the serial port to be ready for writing
    int retval = select(serial_fd + 1, NULL, &writefds, NULL, &timeout);

    if (retval == -1) {
        perror("select");
        close(serial_fd);
        exit(EXIT_FAILURE);
    } else if (retval) {
        if (FD_ISSET(serial_fd, &writefds)) {
            // Write data to the serial port
            while (total_written < data_length) {
                bytes_written = write(serial_fd, data_to_send + total_written, data_length - total_written);
                if (bytes_written == -1) {
                    perror("write");
                    break;  // Exit the loop on error
                }
                total_written += bytes_written;
            }
            if (total_written == data_length) {
                printf("All data sent successfully.\n");
            } else {
                printf("Partial data sent, total bytes written: %zu\n", total_written);
            }
        }
    } else {
        printf("No activity on the serial port within 5 seconds.\n");
    }

    // Close the serial port
    close(serial_fd);
    return 0;
}
