#include <stdio.h>
#include <stdio.h>

int checksum() {
    unsigned int parts[9];
    unsigned int sum;
    printf("Enter the parts:\n");
    for (int i = 0; i < 9; i++) {
        scanf("%X", &parts[i]);
        sum += parts[i];
        while (sum >> 16)
            sum = (sum & 0xffff) + (sum >> 16);
    }
    return ~sum;
}

int main() {
    printf("--- SENDER ---\n");
    int sender_checksum = checksum();
    printf("\n--- RECV ---\n");
    int recv_checksum = checksum();
    printf("Sent checksum: %x\n", sender_checksum);
    printf("Recieved checksum: %x\n", recv_checksum);
    if (sender_checksum == recv_checksum) {
        printf("Matching checksums!\n");
        return 0;
    } else {
        printf("Mismatched checksums!\n");
        return 0;
    }

}

// 00004500 00000073 00000000 00004000 00004011 0000c0a8 00000001 0000c0a8 000000c7
// checksum - ffffb861

// 00004500 0000003c 00001c46 00004000 00004006 0000ac10 00000a63 0000ac10 00000a0c
// checksum - 0000b1e6

