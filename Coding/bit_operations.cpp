/*
 * BITWISE OPERATIONS FOR EMBEDDED SYSTEMS
 * Practice Notebook - Complete these functions to master bitwise operations
 * 
 * Prerequisites: Basic C++ knowledge
 * Target: Embedded systems programming skills
 */

#include <iostream>
#include <bitset>
#include <cstdint>

using namespace std;

// Helper function to display binary representation
void showBinary(const string& label, uint32_t value, int bits = 8) {
    cout << label << ": 0x" << hex << value << " = 0b";
    for (int i = bits - 1; i >= 0; i--) {
        cout << ((value >> i) & 1);
        if (i % 4 == 0 && i != 0) cout << "_";
    }
    cout << " (decimal: " << dec << value << ")" << endl;
}

/*
 * LEARNING AIM: Understanding basic bit setting operations
 * This is fundamental for controlling individual GPIO pins, enabling peripherals,
 * and setting configuration flags in registers.
 */
uint8_t question1_setBit(uint8_t value, uint8_t bitPosition) {
    // TODO: Set the bit at 'bitPosition' to 1
    // Example: setBit(0b00000000, 3) should return 0b00001000
    // Hint: Use OR operation with a shifted 1

    // Thik about (1<<bitPosition) like padding the 1 with bitPosition amount of 0's so 1<<3 is 1000!
    // The or operation is used because we want a 1 no matter what was already there
    return value |= (1<<bitPosition); // Replace with your solution
}

/*
 * LEARNING AIM: Understanding bit clearing operations
 * Essential for disabling features, turning off LEDs, resetting flags,
 * and clearing interrupt flags in status registers.
 */
uint8_t question2_clearBit(uint8_t value, uint8_t bitPosition) {
    // TODO: Clear the bit at 'bitPosition' to 0
    // Example: clearBit(0b11111111, 3) should return 0b11110111
    // Hint: Use AND operation with inverted mask
    
    // Think about the setting of the bit in the same way as before
    /* You set the position you want to clear to be a 1 first. 
       Since you want to clear a bit, the easiest way is to use the AND operation
       Then flip the setting bit to be a 0, thatway the AND will always give 0!  
    */ 
    return value &= ~(1<<bitPosition); // Replace with your solution
}

/*
 * LEARNING AIM: Understanding bit toggling operations
 * Useful for blinking LEDs, toggling states, implementing state machines,
 * and creating alternating patterns in embedded systems.
 */
uint8_t question3_toggleBit(uint8_t value, uint8_t bitPosition) {
    // TODO: Toggle (flip) the bit at 'bitPosition'
    // Example: toggleBit(0b10101010, 0) should return 0b10101011
    // Hint: Use XOR operation
    
    // Think XOR as one or the other, but never both!
    return value ^= (1<<bitPosition); // Replace with your solution
}

/*
 * LEARNING AIM: Checking bit states without modifying them
 * Critical for reading sensor states, checking if peripherals are ready,
 * polling status registers, and making decisions based on hardware states.
 */
bool question4_checkBit(uint8_t value, uint8_t bitPosition) {
    // TODO: Return true if bit at 'bitPosition' is 1, false if 0
    // Example: checkBit(0b10101010, 1) should return true
    // Hint: Use AND operation and shift
    uint8_t test = value;
    test &= (1<<bitPosition);
    return test>>bitPosition; // Replace with your solution
    // Better solution is : return (value & (1 << bitPosition)) != 0; Here if the value is above 0 you know the bit is set.
}

/*
 * LEARNING AIM: Multi-bit masking operations
 * Essential for configuring multi-bit fields in registers (e.g., setting
 * baud rates, prescaler values, ADC channels, timer modes).
 */
uint8_t question5_setMultipleBits(uint8_t value, uint8_t mask, uint8_t newBits) {
    // TODO: Clear bits specified by mask, then set them to newBits
    // Example: setMultipleBits(0b11111111, 0b00001111, 0b00000101)
    //          should return 0b11110101
    // This is used to change specific fields without affecting other bits
    // Hint: Clear with ~mask, then OR with newBits
    value &= ~mask;
    value |= (newBits & mask); // Have to & with the mask so you avoid altering other bits!

    return value; // Replace with your solution
}

/*
 * LEARNING AIM: Extracting bit fields from registers
 * Crucial for reading multi-bit values like ADC results, timer counts,
 * error codes, and configuration settings from hardware registers.
 */
uint8_t question6_extractBitField(uint16_t value, uint8_t startBit, uint8_t numBits) {
    // TODO: Extract 'numBits' bits starting from 'startBit'
    // Example: extractBitField(0b1111000011110000, 4, 4) should return 0b1111
    // Hint: Right shift and mask with (1 << numBits) - 1

    // You need to assign the shift back if you want it to work, this: extracted >> startBit doesn't change extracted it is just an operation
    // You are not clearing bits, so you are not inverting the &!
    uint16_t extracted = value >> startBit;
    uint16_t mask = (1<<numBits)-1;
    extracted &= mask;

    return extracted; // Replace with your solution
}

/*
 * LEARNING AIM: Bit rotation operations
 * Used in cryptographic algorithms, circular buffers, generating
 * pseudo-random sequences, and implementing certain communication protocols.
 */
uint8_t question7_rotateBitsLeft(uint8_t value, uint8_t positions) {
    // TODO: Rotate bits left by 'positions' (circular shift)
    // Example: rotateBitsLeft(0b10110001, 1) should return 0b01100011
    // Hint: Combine left shift with right shift of overflow bits
    
    value = (value<< positions | value>>(8-positions));
    return value; // Replace with your solution
}

/*
 * LEARNING AIM: Counting set bits (Hamming weight)
 * Useful for parity checking, counting active sensors/devices,
 * calculating checksums, and optimizing power consumption analysis.
 */
uint8_t question8_countSetBits(uint32_t value) {
    // TODO: Count the number of 1s in the binary representation
    // Example: countSetBits(0b10110110) should return 5
    // Hint: Use Brian Kernighan's algorithm or iterate through bits
    uint32_t result = value;
    uint32_t bits = 0;
    while(result!=0){
        result &= (result-1);
        bits+=1;
    }
    return bits; // Replace with your solution
}

/*
 * LEARNING AIM: Finding position of highest set bit
 * Important for priority encoding, finding highest priority interrupt,
 * logarithmic calculations, and normalizing values in fixed-point math.
 */
int8_t question9_findMSB(uint32_t value) {
    // TODO: Find position of most significant bit (highest 1)
    // Return -1 if value is 0
    // Example: findMSB(0b00010110) should return 4
    // Hint: Scan from left or use successive right shifts
    if(value == 0){
        return -1;
    }
    uint8_t msb = 0;
    while(value >>= 1 != 0){ // The idea is to right shift until the value is 0, then you get the position of the msb
        msb++;
    }

    return msb; // Replace with your solution
}

/*
 * LEARNING AIM: Reversing bit order
 * Used in FFT algorithms, display mirroring, certain communication
 * protocols (LSB/MSB conversion), and lookup table optimizations.
 */
uint8_t question10_reverseBits(uint8_t value) {
    // TODO: Reverse the order of all bits
    // Example: reverseBits(0b10110001) should return 0b10001101
    // Hint: Swap pairs, then nibbles, or use bit-by-bit approach

    uint8_t result = 0;
    for (int i = 0; i < 8; i++) {
        result <<= 1;          // make space for next bit
        result |= (value & 1); // copy lowest bit from value
        value >>= 1;           // shift value to get next bit
    }
    return result; // Replace with your solution
}

/*
 * LEARNING AIM: Parity calculation
 * Essential for error detection in communication protocols,
 * memory systems, and data integrity checking.
 */
bool question11_calculateParity(uint8_t value) {
    // TODO: Return true for odd parity (odd number of 1s), false for even
    // Example: calculateParity(0b10110010) should return false (4 ones = even)
    // Hint: XOR all bits together
    
    return false; // Replace with your solution
}

/*
 * LEARNING AIM: Sign extension for different bit widths
 * Critical when working with signed values from ADCs, sensors,
 * or when interfacing between systems with different word sizes.
 */
int16_t question12_signExtend(uint8_t value, uint8_t signBitPos) {
    // TODO: Sign-extend a value from signBitPos to 16 bits
    // Example: signExtend(0b11110000, 7) with sign bit at position 7
    //          should return 0xFFF0 (negative number preserved)
    // Hint: Check sign bit and fill upper bits accordingly
    
    return 0; // Replace with your solution
}

/*
 * LEARNING AIM: Atomic bit manipulation simulation
 * Understanding atomic operations for interrupt-safe code,
 * multi-threaded embedded systems, and critical sections.
 */
bool question13_testAndSet(uint8_t& value, uint8_t bitPosition) {
    // TODO: Atomically test if bit is 0, set it to 1, return previous state
    // This simulates test-and-set operation used in mutexes/semaphores
    // Example: if value=0b00000000, testAndSet(value, 3) sets bit 3
    //          and returns false (was 0)
    
    return false; // Replace with your solution
}

/*
 * LEARNING AIM: Gray code conversion
 * Used in rotary encoders, error correction, state machines,
 * and reducing switching activity in digital circuits.
 */
uint8_t question14_binaryToGray(uint8_t binary) {
    // TODO: Convert binary number to Gray code
    // Example: binaryToGray(0b00000011) should return 0b00000010
    // Gray code changes only one bit between successive values
    // Hint: Gray = binary XOR (binary >> 1)
    
    return 0; // Replace with your solution
}

/*
 * LEARNING AIM: Bit-level absolute value without branching
 * Important for DSP operations, real-time systems where
 * branch prediction misses are costly, and SIMD operations.
 */
int8_t question15_absoluteValue(int8_t value) {
    // TODO: Calculate absolute value using only bitwise operations
    // No if statements or ternary operators allowed!
    // Example: absoluteValue(-5) should return 5
    // Hint: Use sign bit mask and XOR properties
    
    return 0; // Replace with your solution
}

// Test harness
void runTests() {
    cout << "\n=== BITWISE OPERATIONS TEST RESULTS ===\n\n";
    
    // Test Question 1
    cout << "Q1 - Set Bit: ";
    uint8_t q1_result = question1_setBit(0b00000000, 3);
    showBinary("Result", q1_result);
    cout << "Expected: 0x8 = 0b0000_1000\n\n";
    
    // Test Question 2
    cout << "Q2 - Clear Bit: ";
    uint8_t q2_result = question2_clearBit(0b11111111, 3);
    showBinary("Result", q2_result);
    cout << "Expected: 0xf7 = 0b1111_0111\n\n";
    
    // Test Question 3
    cout << "Q3 - Toggle Bit: ";
    uint8_t q3_result = question3_toggleBit(0b10101010, 0);
    showBinary("Result", q3_result);
    cout << "Expected: 0xab = 0b1010_1011\n\n";
    
    // Test Question 4
    cout << "Q4 - Check Bit: ";
    bool q4_result = question4_checkBit(0b10101010, 1);
    cout << "Result: " << (q4_result ? "true" : "false") << endl;
    cout << "Expected: true\n\n";
    
    // Test Question 5
    cout << "Q5 - Set Multiple Bits: ";
    uint8_t q5_result = question5_setMultipleBits(0b11111111, 0b00001111, 0b00000101);
    showBinary("Result", q5_result);
    cout << "Expected: 0xf5 = 0b1111_0101\n\n";
    
    // Test Question 6
    cout << "Q6 - Extract Bit Field: ";
    uint8_t q6_result = question6_extractBitField(0b1111000011110000, 4, 4);
    showBinary("Result", q6_result);
    cout << "Expected: 0xf = 0b0000_1111\n\n";
    
    // Test Question 7
    cout << "Q7 - Rotate Left: ";
    uint8_t q7_result = question7_rotateBitsLeft(0b10110001, 1);
    showBinary("Result", q7_result);
    cout << "Expected: 0x63 = 0b0110_0011\n\n";
    
    // Test Question 8
    cout << "Q8 - Count Set Bits: ";
    uint8_t q8_result = question8_countSetBits(0b10110110);
    cout << "Result: " << (int)q8_result << endl;
    cout << "Expected: 5\n\n";
    
    // Test Question 9
    cout << "Q9 - Find MSB: ";
    int8_t q9_result = question9_findMSB(0b00010110);
    cout << "Result: " << (int)q9_result << endl;
    cout << "Expected: 4\n\n";
    
    // Test Question 10
    cout << "Q10 - Reverse Bits: ";
    uint8_t q10_result = question10_reverseBits(0b10110001);
    showBinary("Result", q10_result);
    cout << "Expected: 0x8d = 0b1000_1101\n\n";
    
    // Test Question 11
    cout << "Q11 - Calculate Parity: ";
    bool q11_result = question11_calculateParity(0b10110010);
    cout << "Result: " << (q11_result ? "odd" : "even") << endl;
    cout << "Expected: even\n\n";
    
    // Test Question 12
    cout << "Q12 - Sign Extend: ";
    int16_t q12_result = question12_signExtend(0b10000101, 7);
    cout << "Result: 0x" << hex << (q12_result & 0xFFFF) << dec << endl;
    cout << "Expected: 0xff85\n\n";
    
    // Test Question 13
    cout << "Q13 - Test and Set: ";
    uint8_t q13_value = 0b00000000;
    bool q13_was_set = question13_testAndSet(q13_value, 3);
    cout << "Previous state: " << (q13_was_set ? "1" : "0") << endl;
    showBinary("New value", q13_value);
    cout << "Expected: Previous=0, New=0b0000_1000\n\n";
    
    // Test Question 14
    cout << "Q14 - Binary to Gray: ";
    uint8_t q14_result = question14_binaryToGray(0b00000011);
    showBinary("Result", q14_result);
    cout << "Expected: 0x2 = 0b0000_0010\n\n";
    
    // Test Question 15
    cout << "Q15 - Absolute Value: ";
    int8_t q15_result = question15_absoluteValue(-5);
    cout << "Result: " << (int)q15_result << endl;
    cout << "Expected: 5\n\n";
}


int main() {
    cout << "BITWISE OPERATIONS FOR EMBEDDED SYSTEMS\n";
    cout << "========================================\n";
    cout << "Complete each function, then run tests to check your solutions.\n";
    cout << "These operations are fundamental for:\n";
    cout << "- GPIO control\n";
    cout << "- Register manipulation\n";
    cout << "- Protocol implementation\n";
    cout << "- Memory-efficient data storage\n";
    cout << "- Interrupt handling\n";
    cout << "- Real-time system optimization\n";
    
    runTests();
    
    // Uncomment to see solutions after attempting
    // showSolutions();
    
    return 0;
}