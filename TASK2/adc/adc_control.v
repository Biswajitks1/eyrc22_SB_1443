// SB : Task 2 A : ADC
/*
Instructions
-------------------
Students are not allowed to make any changes in the Module declaration.
This file is used to design ADC Controller.

Recommended Quartus Version : 19.1
The submitted project file must be 19.1 compatible as the evaluation will be done on Quartus Prime Lite 19.1.

Warning: The error due to compatibility will not be entertained.
-------------------
*/

//ADC Controller design
//Inputs  : clk_50 : 50 MHz clock, dout : digital output from ADC128S022 (serial 12-bit)
//Output  : adc_cs_n : Chip Select, din : Ch. address input to ADC128S022, adc_sck : 2.5 MHz ADC clock,
//				d_out_ch5, d_out_ch6, d_out_ch7 : 12-bit output of ch. 5,6 & 7,
//				data_frame : To represent 16-cycle frame (optional)

//////////////////DO NOT MAKE ANY CHANGES IN MODULE//////////////////
module adc_control(
	input  clk_50,				//50 MHz clock
	input  dout,				//digital output from ADC128S022 (serial 12-bit)
	output adc_cs_n,			//ADC128S022 Chip Select
	output din,					//Ch. address input to ADC128S022 (serial)
	output adc_sck,			//2.5 MHz ADC clock
	output [11:0]d_out_ch5,	//12-bit output of ch. 5 (parallel)
	output [11:0]d_out_ch6,	//12-bit output of ch. 6 (parallel)
	output [11:0]d_out_ch7,	//12-bit output of ch. 7 (parallel)
	output [1:0]data_frame	//To represent 16-cycle frame (optional)
);
////////////////////////WRITE YOUR CODE FROM HERE////////////////////
PWM_Generator pulse (.clk(clk_50),.PWM_OUT(adc_sck),.DUTY_CYCLE(50));
reg [4:0]count=0;
reg cout1=0;
reg [2:0]ref=0;
reg [11:0] temp;
reg [11:0] val=0;
reg [11:0] valA=0;
reg [11:0] valB=0;
reg [11:0] i;
assign din=cout1;

always @(negedge adc_sck)begin
 if(ref==0)begin
	count=count+1;
	if(count>=3 && count<4)
		cout1=1;
	if(count>=4 && count<5)
		cout1=0;
	if(count>=5 && count<6)begin
		cout1=1;
		//temp[11]=dout;
	end
	if(count<=6)
		temp[11]=dout;
  for(i=1;i<=11;i=i+1)begin
		if((count>=i+5) && (count<=i+6))begin
			temp[11-i]=dout;
			cout1=0;
			end
	end
	if(count>=17)begin
		val<=temp;
		count=0;
		ref=1;
	end
	end
	if(ref==1)begin
	count=count+1;
	if(count>=3 && count<4)begin
		cout1=1;
	end
	if(count>=4 && count<5)
		cout1=1;
	if(count>=5 && count<6)
		cout1=0;
	if(count<=6)
		temp[11]=dout;
  for(i=1;i<=11;i=i+1)begin
		if((count>=i+5) && (count<=i+6))begin
			temp[11-i]=dout;
			cout1=0;
			end
	end
	if(count>=17)begin
		valA<=temp;
		count=0;
		ref=2;
	end
	end
	if(ref==2)begin
	count=count+1;
	if(count>=3 && count<4)begin
		cout1=1;
	end
	if(count>=4 && count<5)
		cout1=1;
	if(count>=5 && count<6)
		cout1=1;
	if(count<=6)
		temp[11]=dout;
  for(i=1;i<=11;i=i+1)begin
		if((count>=i+5) && (count<=i+6))begin
			temp[11-i]=dout;
			cout1=0;
			end
	end
	if(count>=17)begin
		valB<=temp;
		count=0;
		ref=3;
	end
	end
end
assign d_out_ch7=val;
assign d_out_ch5=valA;
assign d_out_ch6=valB;
////////////////////////YOUR CODE ENDS HERE//////////////////////////
endmodule
///////////////////////////////MODULE ENDS///////////////////////////