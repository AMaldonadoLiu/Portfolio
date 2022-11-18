module top;
integer data_file;
integer valid_data;
integer data_command;
string retrieved_file;
integer debug;
reg flag = 0;
reg[63:0] read_address;








initial
begin
//look for file name
if($test$plusargs ("debug"))
	debug = 1;
if($value$plusargs ("FILENAME=%s", retrieved_file))
    $display("Received file name");
else
	begin
	$display("No file name received");
	$finish;
	end
//open file
#10
data_file = $fopen(retrieved_file, "r");
if(data_file == 0)
	begin
	$display("Unable to open file");
	$finish;
	end

while(!$feof(data_file))
	begin
	valid_data = $fscanf(data_file, "%d", data_command);
	if(valid_data != 0)
		begin
		if(debug == 1)
			$display("Read command number: ", data_command);
		//send data into modules
		end
	else
		begin
		$display("No command read.");
		$finish;
		end

	valid_data = $fscanf(data_file, "%h", read_address);
	if(valid_data != 0)
		begin
		if(debug == 1)
			$displayh("Read address: ", read_address);
		//send data into modules
		end
	else
		begin
		$display("No address read.");
		$finish;
		end
		
    	if($test$plusargs ("silent"))
    	$display("silent mode");
   	if($test$plusargs("normal"))
    	$display("normal mode");


	end
$fclose(data_file);
end
	
endmodule
