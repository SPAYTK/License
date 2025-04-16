// bloch_energy_out_complex.v
// FPGA Module: Calculates frequency output as a complex number (Real/Imag)
// According to the consensus formula:
// f_out = (x * t * Bloch(theta, phi)) / ((9/8)*(pi/3)) * exp(i*phi)

module bloch_energy_out_complex (
    input wire clk,                    // System clock
    input wire reset_n,               // Active-low reset
    input wire trigger,               // Trigger from clk_pi_pulse
    input wire [31:0] x_in,           // Position input (scaled meters)
    input wire [31:0] t_in,           // Time input (scaled seconds)
    input wire [31:0] theta_in,       // Theta (radians)
    input wire [31:0] phi_in,         // Phi (radians)
    output reg [15:0] out_freq_real,  // Output: Real part of frequency
    output reg [15:0] out_freq_imag,  // Output: Imaginary part of frequency
    output reg valid                  // Output valid flag
);

    real pi = 3.1415926535;
    real f_base;
    real bloch_proj;
    real E_consenso;
    real real_out, imag_out;

    initial begin
        f_base = (9.0 / 8.0) * (pi / 3.0); // Calculated only once
    end

    always @(posedge clk or negedge reset_n) begin
        if (!reset_n) begin
            out_freq_real <= 0;
            out_freq_imag <= 0;
            valid <= 0;
        end else if (trigger) begin
            bloch_proj = $cos(phi_in) * $sin(theta_in);
            E_consenso = (x_in * t_in * bloch_proj) / f_base;
            real_out = E_consenso * $cos(phi_in);
            imag_out = E_consenso * $sin(phi_in);
            out_freq_real <= $rtoi(real_out);
            out_freq_imag <= $rtoi(imag_out);
            valid <= 1;
        end else begin
            valid <= 0;
        end
    end

endmodule
