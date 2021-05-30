program Omni_Line_Pascal;

uses STArduino, STTODRobot;

var chan_cambien:array[0..15] of integer;
var goc_cambien:array[0..15] of real;
var count, angle:integer;
var newAngle:real;

const
    IN1=22;
    IN2=23;
    EN1=5;
    IN3=24;
    IN4=25;
    EN2=6;
    IN5=26;
    IN6=27;
    EN3=7;
    irThreshold = 512;
    angleRange = 60;
    delayDuration = 5;
    
procedure lay_chan_cambien;
begin 
	chan_cambien[0] := A0;
	chan_cambien[1] := A1;
	chan_cambien[2] := A2;
	chan_cambien[3] := A3;
	chan_cambien[4] := A4;
	chan_cambien[5] := A5;
	chan_cambien[6] := A6;
	chan_cambien[7] := A7;
	chan_cambien[8] := A8;
	chan_cambien[9] := A9;
	chan_cambien[10] := A10;
	chan_cambien[11] := A11;
	chan_cambien[12] := A12;
	chan_cambien[13] := A13;
	chan_cambien[14] := A14;
	chan_cambien[15] := A15;	
end;

procedure lay_goc_cambien;
begin 
	goc_cambien[0] := 0;
	goc_cambien[1] := 22.5;
	goc_cambien[2] := 45;
	goc_cambien[3] := 67.5;
	goc_cambien[4] := 90;
	goc_cambien[5] := 112.5;
	goc_cambien[6] := 135;
	goc_cambien[7] := 157.5;
	goc_cambien[8] := 190;
	goc_cambien[9] := 202.5;
	goc_cambien[10] := 225;
	goc_cambien[11] := 247.5;
	goc_cambien[12] := 290;
	goc_cambien[13] := 292.5;
	goc_cambien[14] := 315;
	goc_cambien[15] := 337.5;	
end;

procedure setup;
begin
	lay_chan_cambien;
	lay_goc_cambien;
{Khoi tao}
	todRobotInitialize(IN1, IN2, EN1, IN3, IN4, EN2, IN5, IN6, EN3);
	angle:=0;
end;

procedure find_angle;
var i, minAngle, maxAngle, value:integer;
var varTemp:real;
begin
	minAngle:=angle - angleRange;
	if (minAngle < 0) then
		minAngle:=minAngle+360;
	maxAngle:=angle + angleRange;
	if (maxAngle > 360) then
		maxAngle:=maxAngle-360;	
	if (minAngle < maxAngle)then
	begin
		for i:=0 to 15 do
		begin
			if ((goc_cambien[i] >= minAngle) and (goc_cambien[i] <= maxAngle)) then
			begin
				value := analogRead(chan_cambien[i]);
				if (value > irThreshold) then
				begin
					newAngle := newAngle + goc_cambien[i];
					count:=count+1;
				end;
			end;
		end;
	end
	else
	begin
		for i:= 0 to 15 do
		begin
			if ((goc_cambien[i] >= minAngle) or (goc_cambien[i] <= maxAngle)) then
			begin
				value := analogRead(chan_cambien[i]);
				if (value > irThreshold) then
				begin
					if (goc_cambien[i] <= maxAngle) then
					begin	
						newAngle:= newAngle + goc_cambien[i];
					end	
					else
					begin
						varTemp := goc_cambien[i] - 360;
						newAngle:= varTemp + newAngle;
					end;		
					count:=count+1;
				end;
			end;
		end;
	end;
end;

procedure loop;
begin
	find_angle;
	if (count <> 0) then
	begin
		newAngle:= ((newAngle * 1) / count);
		if (newAngle < 0) then 
			newAngle:= newAngle + 360;	
		angle:= Round(newAngle);
		todRobotMove(angle, 150);
  		delay(delayDuration);						 
	end
	else
		delay(delayDuration);
	count:=0;
	newAngle:=0;		
end;	

begin
	setup;
	loop;
end.
