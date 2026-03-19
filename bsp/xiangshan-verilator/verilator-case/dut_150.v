module dut_150 (
    input clk,
    input resetn,    // active-low synchronous reset
    input [3:1] r,   // request
    output [3:1] g   // grant
  ); 

    parameter a=2'd0, b=2'd1, c=2'd2, d=2'd3;
    reg [1:0] state, next_state;
    
    always@(*) begin
        case(state)
            a: begin
                if(r[1])    next_state = b;
                else if(~r[1] & r[2])   next_state = c;
                else if(~r[1] & ~r[2] & r[3])   next_state = d;
                else    next_state = a;
            end
            b: begin
                if(r[1])    next_state = b;
                else        next_state = a;
            end
            c: begin
                if(r[2])    next_state = c;
                else        next_state = a;
            end
            d: begin
                if(r[3])    next_state = d;
                else        next_state = a;
            end
        endcase
    end

    always@(posedge clk) begin
        if(~resetn)
            state <= a;
        else
            state <= next_state;
    end
    
    assign g[1] = (state == b);
    assign g[2] = (state == c);
    assign g[3] = (state == d);
    
    
endmodule
