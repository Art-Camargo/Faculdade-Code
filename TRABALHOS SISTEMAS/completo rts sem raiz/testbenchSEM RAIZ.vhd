----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03.12.2023 20:50:53
-- Design Name: 
-- Module Name: Testbench - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity testbench is
end testbench;

architecture Behavioral of testbench is
signal clk_tb, start_tb: std_logic := '0';
signal dado_A_tb, dado_B_tb, DADO_C_TB: integer;
signal saida_tb: integer;
component TOPO
	Port (  
	    clk, start : in std_logic;
        a, b, c: in integer;
        z: out integer
        );
end component;

begin
COMB: TOPO port map(
			     clk    => clk_tb,
			     c => DADO_C_TB,
			     a => dado_A_tb,
			     b => dado_B_tb,
			     start=> start_tb,
			     z => saida_tb
			    );
		clk_tb <= not clk_tb after 10ns;
		
        start_tb <=  '1' after 20ns;
		dado_A_tb<= 4 ;
		dado_B_tb<= 2;
		dado_c_tb<= 2 ;
		

end Behavioral;