// SB : Task 2 B : UART
/*
Instructions
-------------------
Students are not allowed to make any changes in the Module declaration.
This file is used to design UART Transmitter.

Recommended Quartus Version : 19.1
The submitted project file must be 19.1 compatible as the evaluation will be done on Quartus Prime Lite 19.1.

Warning: The error due to compatibility will not be entertained.
-------------------
*/

//UART Transmitter design
//Input   : clk_50M : 50 MHz clock
//Output  : tx : UART transmit output

//50MHz/115200=434;

//////////////////DO NOT MAKE ANY CHANGES IN MODULE//////////////////
module uart(
	input clk_50M,	//50 MHz clock
	output tx		//UART transmit output
);
////////////////////////WRITE YOUR CODE FROM HERE////////////////////
reg [7:0] out;
assign tx=out;
parameter [8:0]clks_per_bit=9'b110110010;
parameter idle=8'b001;
parameter tx_start=8'b000;
parameter [7:0]tx_data=8'b00101;
parameter [7:0]tx_data2=8'b00111;
parameter [7:0]tx_data3=8'b01111;
parameter [7:0]tx_data4=8'b11011;
parameter [7:0]tx_data5=8'b11101;
parameter [7:0]tx_data6=8'b11110;
parameter tx_stop=8'b0011;
reg [7:0] s_Main=idle;
reg [21:0] clk_count=0;
reg[7:0] count=1;
always@(posedge clk_50M) begin
	clk_count=clk_count+1;
	case(s_Main)
		idle:if(count<=4)begin
					if(clk_count<=clks_per_bit)begin
						out=1;
					end
					else begin
						s_Main=tx_start;
						clk_count=0;
					 end
				end
				else begin
					out=1;
				end	
		tx_start:if(clk_count<=clks_per_bit)begin
						out=0;
					end
				else begin
						if(count==1)begin
					s_Main=tx_data;
					clk_count=0;
						end
						if(count==2)begin
					s_Main=tx_data2;
					clk_count=0;
						end
						if(count==3)begin
					s_Main=tx_data5;
					clk_count=0;
						end
						if(count==4)begin
					s_Main=tx_data6;
					clk_count=0;
						end
					end
		tx_data:if(clk_count<=clks_per_bit)begin
						out=1;
					end
					else if(clk_count>clks_per_bit && clk_count<=2*clks_per_bit-1)begin
						out=1;
					end
					else if(clk_count>2*clks_per_bit && clk_count<=4*clks_per_bit)begin
						out=0;
					end
					else if(clk_count>4*clks_per_bit && clk_count<=5*clks_per_bit)begin
						out=1;
					end
					else if(clk_count>5*clks_per_bit && clk_count<=6*clks_per_bit)begin
						out=0;
					end
					else if(clk_count>6*clks_per_bit && clk_count<=7*clks_per_bit)begin
						out=1;
					end
					else if(clk_count>7*clks_per_bit && clk_count<=8*clks_per_bit)begin
						out=0;
					end
				   else if(clk_count>8*clks_per_bit)begin
					s_Main=tx_stop;
					count=count+1;
					clk_count=0;
					end
		tx_data2:if(clk_count<=clks_per_bit)begin
						out=0;
					end
					else if(clk_count>clks_per_bit && clk_count<=2*clks_per_bit-1)begin
						out=1;
					end
					else if(clk_count>2*clks_per_bit && clk_count<=6*clks_per_bit)begin
						out=0;
					end
					else if(clk_count>6*clks_per_bit && clk_count<=7*clks_per_bit)begin
						out=1;
					end
					else if(clk_count>7*clks_per_bit && clk_count<=8*clks_per_bit)begin
						out=0;
					end
				   else if(clk_count>8*clks_per_bit)begin
					s_Main=tx_stop;
					clk_count=0;
					count=count+1;
					end
		tx_data5:if(clk_count<=clks_per_bit)begin
						out=0;
					end
					else if(clk_count>clks_per_bit && clk_count<=2*clks_per_bit-1)begin
						out=0;
					end
					else if(clk_count>2*clks_per_bit && clk_count<=3*clks_per_bit)begin
						out=1;
					end					
					else if(clk_count>3*clks_per_bit && clk_count<=4*clks_per_bit)begin
						out=0;
					end
					else if(clk_count>4*clks_per_bit && clk_count<=6*clks_per_bit)begin
						out=1;
					end
					else if(clk_count>6*clks_per_bit && clk_count<=8*clks_per_bit)begin
						out=0;
					end
				   else if(clk_count>8*clks_per_bit)begin
					s_Main=tx_stop;
					clk_count=0;
					count=count+1;
					end
		tx_data6:if(clk_count<=clks_per_bit)begin
						out=1;
					end
					else if(clk_count>clks_per_bit && clk_count<=2*clks_per_bit-1)begin
						out=1;
					end
					else if(clk_count>2*clks_per_bit && clk_count<=4*clks_per_bit)begin
						out=0;
					end
					else if(clk_count>4*clks_per_bit && clk_count<=6*clks_per_bit)begin
						out=1;
					end
					else if(clk_count>6*clks_per_bit && clk_count<=7*clks_per_bit)begin
						out=0;
					end
					else if(clk_count>7*clks_per_bit && clk_count<=8*clks_per_bit)begin
						out=0;
					end
				   else if(clk_count>8*clks_per_bit)begin
					count=count+1;
					s_Main=idle;
					clk_count=0;
					end					
		tx_stop:if(clk_count<=2*clks_per_bit)begin
						out=1;
					end
				  else begin
				    if(count>4)begin
				  s_Main=idle;
				  clk_count=0;
					 end
					 else begin
				  s_Main=tx_start;
				  clk_count=0;
				    end 
				   end
	endcase
end

////////////////////////YOUR CODE ENDS HERE//////////////////////////
endmodule
///////////////////////////////MODULE ENDS///////////////////////////