#pragma config(Sensor, in1,    light,          sensorReflection)
#pragma config(Sensor, in2,    temp,           sensorReflection)
#pragma config(Sensor, dgtl2,  ledBoop1,       sensorDigitalOut)
#pragma config(Sensor, dgtl3,  ledBoop2,       sensorDigitalOut)
#pragma config(Sensor, dgtl4,  ledBoop3,       sensorDigitalOut)
#pragma config(Sensor, dgtl5,  ledBoop4,       sensorDigitalOut)
#pragma config(Sensor, dgtl6,  ledBoop5,       sensorDigitalOut)
#pragma config(Sensor, dgtl7,  ledBoop6,       sensorDigitalOut)
#pragma config(Sensor, dgtl8,  ledBoop7,       sensorDigitalOut)
#pragma config(Sensor, dgtl9,  ledBoop8,       sensorDigitalOut)
#pragma config(Sensor, dgtl10, ledBoop9,       sensorDigitalOut)
#pragma config(Sensor, dgtl11, wind,           sensorQuadEncoder)
#pragma config(Motor,  port2,           flag,          tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port3,           quad,          tmotorVex393_MC29, openLoop, encoderPort, None)
#pragma config(Motor,  port4,           leftMotor,     tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port5,           rightMotor,    tmotorVex393_MC29, openLoop, driveRight)
#pragma config(Motor,  port6,           gravel,        tmotorServoStandard, openLoop)
#pragma config(Motor,  port7,           arm,           tmotorServoContinuousRotation, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma DebuggerWindows("debugStream")
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
*everything on the left is negated because of mirrored motors
*/
#define HALF_SPEED 63;
#define FULL_SPEED 127;
#define STATIONARY 0;
#define BACK_HALF -63;
#define BACK_FULL -127;
int data[9];
int curData = 0;

/*
*turn left without moving forward, pivot turn
*/
void left()
{
	motor[rightMotor] = 63;
	motor[leftMotor] = 63;
	wait1Msec(500);
	motor[rightMotor] = STATIONARY;
	motor[leftMotor] = STATIONARY;
}

void right()
{
	motor[leftMotor] = -63;
	motor[rightMotor] = -63;
	wait1Msec(500);
	motor[rightMotor] = STATIONARY;
	motor[leftMotor] = STATIONARY;
}
void dropFlag()
{
	motor[flag] = 30;
	wait1Msec(500);
	motor[flag] = STATIONARY;
}
void gravelUp()
{
	motor[gravel] = 90;
	wait1Msec(500);
	motor[gravel] = STATIONARY;
}

void gravelDown()
{
	motor[gravel] = -90;
	wait1Msec(500);
	motor[gravel] = STATIONARY;
}

void armDown()
{
	motor[arm] = 30;
	wait1Msec(100);

}
void armUp()
{
	motor[arm] = -30;
	wait1Msec(100);
	motor[arm] = STATIONARY;
}

void toBinary(int num) {
	//number to convert to binary
	int n=num;
	//writeDebugStreamLine("input num (decimal): %d", n);

	wait1Msec(1000);

	// array to store binary number
	int binaryNum[9];
	//setting the whole array to 0
	for (int j = 0; j < 9; j++) {
		binaryNum[j]=0;
	}
	// counter for binary array,
	int i = 0;
	while (n > 0) {
		binaryNum[i]= n % 2;
		n = n / 2;
		i++;
	}
	// printing binary array in reverse order
	//for (int j = 8; j >=0; j--) {
	//writeDebugStream("%d", binaryNum[j]);
	//}
	if(binaryNum[0]==1){
		SensorValue[ledBoop1] = false;
	}
	if(binaryNum[1]==1){
		SensorValue[ledBoop2] = false;
	}
	if(binaryNum[2]==1){
		SensorValue[ledBoop3] = false;
	}
	if(binaryNum[3]==1){
		SensorValue[ledBoop4] = false;
	}
	if(binaryNum[4]==1){
		SensorValue[ledBoop5] = false;
	}
	if(binaryNum[5]==1){
		SensorValue[ledBoop6] = false;
	}
	if(binaryNum[6]==1){
		SensorValue[ledBoop7] = false;
	}
	if(binaryNum[7]==1){
		SensorValue[ledBoop8] = false;
	}
	if(binaryNum[8]==1){
		SensorValue[ledBoop9] = false;
	}
	wait1Msec(6000);
	wait1Msec(1000);
	SensorValue[ledBoop1] = true;
	wait1Msec(300);
	SensorValue[ledBoop2] = true;
	wait1Msec(300);
	SensorValue[ledBoop3] = true;
	wait1Msec(300);
	SensorValue[ledBoop4] = true;
	wait1Msec(300);
	SensorValue[ledBoop5] = true;
	wait1Msec(300);
	SensorValue[ledBoop6] = true;
	wait1Msec(300);
	SensorValue[ledBoop7] = true;
	wait1Msec(300);
	SensorValue[ledBoop8] = true;
	wait1Msec(300);
	SensorValue[ledBoop9] = true;
	wait1Msec(2000);
}
/*
*	Prints all the data in binary on the LED display
* Waits 5 seconds in between each element
*/
void printData(){
	for (int i = 0; i < 9; i++){
		if(data[i]!=0){
			toBinary(data[i]);
			wait1Msec(5000);
		}
	}
	for (int i = 0; i < 9; i++){
		data[i]=0;
	}
	curData=0;
}

void testPrint()
{
	while (true)
	{
		writeDebugStreamLine("sensor value: %d", SensorValue[light]);
		//toBinary(SensorValue[light]/10);
		wait1Msec(2500);
	}

}
/*
* measure temperature once and store in array
*/
void tempSense()
{
	int dataValue = SensorValue[temp];
	writeDebugStreamLine("sensor value b4: %d", dataValue);
	dataValue =((-27.0/209.0)*(dataValue))+1674.0/19.0;
	writeDebugStreamLine("sensor value: %d", dataValue);
	toBinary(dataValue);
	data[curData] = dataValue;
	curData++;

}

void lightSense()

{
	bool looping;
	while(looping){
		motor[rightMotor] = HALF_SPEED;
		motor[leftMotor] = HALF_SPEED;
		if(SensorValue[light]<267){
			wait1Msec(300);
			motor[rightMotor] = STATIONARY;
			motor[leftMotor] = STATIONARY;
			looping=false;
		}
	}
}

void windSense()
{
	int count = 0;
	int now = 0;
	int last = 0;
	while (count < 12) {
		//turns on all the lights
		SensorValue[ledBoop1] = true;
		SensorValue[ledBoop2] = true;
		SensorValue[ledBoop3] = true;
		SensorValue[ledBoop4] = true;
		SensorValue[ledBoop5] = true;
		SensorValue[ledBoop6] = true;
		SensorValue[ledBoop7] = true;
		SensorValue[ledBoop8] = true;
		SensorValue[ledBoop9] = true;
		now = SensorValue[wind];
		int diff = now-last;
		writeDebugStreamLine("sensor value: %d", diff);
		wait1Msec(300);
		if(diff < -1400) {
			SensorValue[ledBoop1]=false;
			SensorValue[ledBoop2]=false;
			SensorValue[ledBoop3]=false;
			wait1Msec(1000);
		}
		else if(diff < -1000) {
			SensorValue[ledBoop1]=false;
			SensorValue[ledBoop2]=false;
			wait1Msec(1000);
		}
		else if(diff < -500) {
			SensorValue[ledBoop1]=false;
			wait1Msec(1000);
		}
		else{
			wait1Msec(1000);
		}
		last = now;
		count++;
	}
	//turns on all the lights
	SensorValue[ledBoop1] = true;
	SensorValue[ledBoop2] = true;
	SensorValue[ledBoop3] = true;
	SensorValue[ledBoop4] = true;
	SensorValue[ledBoop5] = true;
	SensorValue[ledBoop6] = true;
	SensorValue[ledBoop7] = true;
	SensorValue[ledBoop8] = true;
	SensorValue[ledBoop9] = true;
	now = SensorValue[wind];
	int diff = now-last;
	writeDebugStreamLine("sensor value: %d", diff);
	wait1Msec(300);
	if(diff < -1400) {
		SensorValue[ledBoop1]=false;
		SensorValue[ledBoop2]=false;
		SensorValue[ledBoop3]=false;
		data[curData]=4;
		wait1Msec(1000);
	}
	else if(diff < -900) {
		SensorValue[ledBoop1]=false;
		SensorValue[ledBoop2]=false;
		data[curData]=2;
		wait1Msec(1000);
	}
	else if(diff < -500) {
		SensorValue[ledBoop1]=false;
		data[curData]=1;
		wait1Msec(1000);
	}
	else{
		wait1Msec(1000);
	}
curData++:
	SensorValue[ledBoop1] = true;
	SensorValue[ledBoop2] = true;
	SensorValue[ledBoop3] = true;
	SensorValue[ledBoop4] = true;
	SensorValue[ledBoop5] = true;
	SensorValue[ledBoop6] = true;
	SensorValue[ledBoop7] = true;
	SensorValue[ledBoop8] = true;
	SensorValue[ledBoop9] = true;
}
void autoMove() {
	//wu glacier (should be pointed to piper pond
//forward
	motor[rightMotor] = HALF_SPEED;
	motor[leftMotor] = -HALF_SPEED;
	wait1Msec(2000);
	//right
	motor[rightMotor] = -HALF_SPEED;
	motor[leftMotor] = -HALF_SPEED;
	wait1Msec(900);
	//stop
	motor[rightMotor] = STATIONARY;
	motor[leftMotor] = STATIONARY;
	//asd A As
	armDown();
	armDown();
	tempSense();
	wait1Msec(1000);
	//back
	motor[rightMotor] = -HALF_SPEED;
	motor[leftMotor] = HALF_SPEED;
	wait1Msec(500);
	lightSense();
	//left
	motor[rightMotor] = HALF_SPEED;
	motor[leftMotor] = HALF_SPEED;
	wait1Msec(1300);
	motor[rightMotor] = STATIONARY;
	motor[leftMotor] = STATIONARY;
}

void move()
{
	//turns off all the lights
	SensorValue[ledBoop1] = false;
	SensorValue[ledBoop2] = false;
	SensorValue[ledBoop3] = false;
	SensorValue[ledBoop4] = false;
	SensorValue[ledBoop5] = false;
	SensorValue[ledBoop6] = false;
	SensorValue[ledBoop7] = false;
	SensorValue[ledBoop8] = false;
	SensorValue[ledBoop9] = false;

	wait1Msec(1000);
	SensorValue[ledBoop1] = true;
	wait1Msec(100);
	SensorValue[ledBoop2] = true;
	wait1Msec(100);
	SensorValue[ledBoop3] = true;

	wait1Msec(100);
	SensorValue[ledBoop4] = true;
	wait1Msec(100);
	SensorValue[ledBoop5] = true;
	wait1Msec(100);
	SensorValue[ledBoop6] = true;
	wait1Msec(100);
	SensorValue[ledBoop7] = true;
	wait1Msec(100);
	SensorValue[ledBoop8] = true;
	wait1Msec(100);
	SensorValue[ledBoop9] = true;

	while(true) {
		if(vexRT[Btn7u] == 1){
			motor[rightMotor] = HALF_SPEED;
			motor[leftMotor] = -HALF_SPEED;
		}
		else if(vexRT[Btn7d] == 1){
			motor[rightMotor] = -HALF_SPEED;
			motor[leftMotor] = HALF_SPEED;
		}
		else if(vexRT[Btn7r] == 1){
			motor[rightMotor] = -HALF_SPEED;
			motor[leftMotor] = -HALF_SPEED;
		}
		else if(vexRT[Btn7l] == 1){
			motor[rightMotor] = HALF_SPEED;
			motor[leftMotor] = HALF_SPEED;
		}
		else{
			motor[rightMotor] = STATIONARY;
			motor[leftMotor] = STATIONARY;
		}
		if(vexRT[Btn6D] == 1){
			windSense();
		}
		if(vexRT[Btn5U] == 1){
			lightSense();
		}
		if(vexRT[Btn5D] == 1){
			autoMove();
		}
		if(vexRT[Btn6U] == 1){
			dropFlag();
		}
		if(vexRT[Btn8U] == 1){
			gravelUp();
		}
		if(vexRT[Btn8D] == 1){
			gravelDown();
		}
		if(vexRT[Btn8R] == 1){
			armDown();
		}
		if(vexRT[Btn8L] == 1){
			armUp();
		}
		if(vexRT[ch3] >10){
			printData();
		}
		if(vexRT[ch2] >10){
			tempSense();
		}
	}
}

task main()

{
	//left();
	//right();
	//tempSense();
	move();//sweet
}
