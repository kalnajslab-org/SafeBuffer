/*  SafeBuffer_Test.ino
 *  Author: Alex St. Clair
 *  Created: July 2019
 * 
 *  Test Arduino script for the SafeBuffer.
 *  
 *  Note: errors for the serial echo are due to Arduino internal buffering
 */
 
 #include <SafeBuffer.h>

uint8_t buffer_array[4] = {0};
SafeBuffer buff(buffer_array, 4);

char terminal_buffer_array[100] = {0};
SafeBuffer term_buff((uint8_t *) terminal_buffer_array, 100);

volatile bool error_flag = false;
char temp_char = '\0';

void serialEvent()
{
  while (Serial.available()) {
    if (!term_buff.Push(Serial.read())) {
      error_flag = true;
    }
  }
}

void setup()
{
  Serial.begin(115200);
  delay(5000);
  uint8_t temp = 0;

  Serial.println("-- Test beginning --");

  // Empty buffer tests
  if (!buff.IsEmpty()) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (buff.IsFull()) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (buff.NumElements() != 0) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (buff.Pop(&temp)) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (buff.Peek(&temp)) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }

  // 0/4 -> 1/4
  if (!buff.Push(1)) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (buff.IsEmpty()) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (buff.IsFull()) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (buff.NumElements() != 1) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (!buff.Peek(&temp) || temp != 1) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }

  // 1/4 -> 4/4
  if (!buff.Push(2)) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (!buff.Push(3)) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (!buff.Push(4)) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (!buff.IsFull()) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (buff.Push(99)) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (!buff.IsFull()) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (buff.NumElements() != 4) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }

  // 4/4 -> 2/4
  if (!buff.Peek(&temp) || temp != 1) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (!buff.Pop(&temp) || temp != 1) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (!buff.Pop(&temp) || temp != 2) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (buff.IsEmpty()) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (buff.IsFull()) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (buff.NumElements() != 2) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }

  // 2/4 -> 4/4
  if (!buff.Push(5)) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (!buff.Push(6)) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (!buff.IsFull()) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (buff.Push(99)) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (!buff.IsFull()) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (buff.NumElements() != 4) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }

  // 4/4 -> 0/4
  if (!buff.Peek(&temp) || temp != 3) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (!buff.Pop(&temp) || temp != 3) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (!buff.Pop(&temp) || temp != 4) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (!buff.Pop(&temp) || temp != 5) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (!buff.Pop(&temp) || temp != 6) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (!buff.IsEmpty()) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (buff.NumElements() != 0) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  
  // 0/4 -> 4/4
  if (!buff.Push(7)) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (!buff.Push(8)) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (!buff.Push(9)) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (!buff.Push(10)) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (!buff.IsFull()) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (buff.NumElements() != 4) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }

  // 4/4 -> 1/4
  if (!buff.Pop(&temp) || temp != 7) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (!buff.Pop(&temp) || temp != 8) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (!buff.Pop(&temp) || temp != 9) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (buff.NumElements() != 1) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }

  // 1/4 -> 4/4
  if (!buff.Push(11)) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (!buff.Push(12)) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (!buff.Push(13)) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (!buff.IsFull()) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (buff.Push(99)) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (!buff.IsFull()) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (buff.IsEmpty()) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }

  // 4/4 -> 0/4
  if (!buff.Pop(&temp) || temp != 10) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (!buff.Pop(&temp) || temp != 11) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (!buff.Pop(&temp) || temp != 12) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (!buff.Peek(&temp) || temp != 13) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (!buff.Pop(&temp) || temp != 13) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (!buff.IsEmpty()) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (buff.NumElements() != 0) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (buff.Pop(&temp)) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (buff.Peek(&temp)) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }

  // 0/4 -> 1/4
  if (!buff.Push(14)) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (buff.NumElements() != 1) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }

  // 1/4 -> 0/4
  buff.Clear();
  if (buff.NumElements() != 0) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (!buff.IsEmpty()) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }

  // 0/4 -> 4/4
  if (!buff.Push(15)) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (!buff.Push(16)) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (!buff.Push(17)) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (!buff.Push(18)) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }

  // 4/4 -> 0/4
  buff.Clear();
  if (buff.NumElements() != 0) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }
  if (!buff.IsEmpty()) {
    Serial.print("Err line: "); Serial.println(__LINE__);
  }

  Serial.println("-- Test complete --");
}

void loop()
{
  if (error_flag) {
    error_flag = false;
    Serial.println("-error-");
  }

  // print from the buffer
  while (term_buff.Pop((uint8_t *) &temp_char)) {
    Serial.print(temp_char);
  }

  delay(500);
}

