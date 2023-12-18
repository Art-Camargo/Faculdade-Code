----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05.12.2023 19:01:24
-- Design Name: 
-- Module Name: UnidadeOperativa - Behavioral
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


entity UnidadeOperativa is
      Port (
               clk, acc: in std_logic;
               a: in integer;
               b: in integer;
               C: in integer;
               M2: in std_logic_vector(1 downto 0);
               M1: in std_logic_vector(2 downto 0);
               ULAOP: in std_logic;
               Z: out integer
      );
end UnidadeOperativa;

architecture Behavioral of UnidadeOperativa is
     signal M2OUT, M1OUT, ULAOUT, ACCOUT: integer;
begin
    
    
    Mux1 : process(M1)
           begin
           
                case M1 is
                    when "000" => M1OUT <= a;
                    when "001" => M1OUT <= b;
                    when "010" => M1OUT <= c;
                    when "011" => M1OUT <= 5;
                    when "100" => M1OUT <= 6;
                    when "101" => M1OUT <= ULAOUT;
                    when others => M1OUT <= M1OUT;
                end case;
          
     end process Mux1;
     
     Mux2 : process(M2)
           
           begin
           
                case M2 is
                    when "00" => M2OUT <= a; 
                    when "01" => M2OUT <= b;
                    when "10" => M2OUT <= c;
                    when others => M2OUT <= ACCOUT;
                    
                end case;
            
            
     end process Mux2;
    
    ULA : process(ULAOP, M1OUT, M2OUT)
           begin
           
                case ULAOP is
                    when '1' => ULAOUT <= (M1OUT * M2OUT);
                    when others => ULAOUT <= (M1OUT + M2OUT);
                end case;
            
            
     end process ULA;
     
     process(acc, clk)
           begin
                if(clk'EVENT AND clk = '1') then
                    if acc = '1' then
                        ACCOUT <= ULAOUT;
                    end if;
                end if;
     end process;
     
    z <= ULAOUT;
end Behavioral;
