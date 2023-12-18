---------------------------------------------------------------------
-- Company:      UERGS
-- Engineer:     Artur de Camargo e Julio Augusto de Castilhos Borges
-- Create Date:  11/08/2023 09:05:50 AM
-- Design Name:  Unicade Operativa
-- Module Name:  Unidade Operativa - Behavioral
-- Project Name: TrabSistemas
-- Description:
---------------------------------------------------------------------

-- se (a > b e a > c), fazer 6a.b.c + 5acc; senão fazer (√abc)

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;

entity UnidadeControle is
    Port(
          ULAOP: out std_logic;
             M2: out std_logic_vector(1 downto 0);
             acc: out std_logic;
             M1: out std_logic_vector(2 downto 0);
             clk, start: in std_logic;
             a, b, c: in integer
    );
end UnidadeControle;

architecture rtl of UnidadeControle is

TYPE State_type IS (IDLE, AA, BB, CC, D, E, F, G, H);
SIGNAL nextstate: State_type;
signal current:  State_type;
   
        
begin
 main : process(clk, nextstate)
            begin
                if (clk'event and clk='1') then
                    current <= nextstate; 
                end if;
        
        end process main; 
        
        
  next_state : process(current, nextstate, clk)  
        begin
            case current is
                when IDLE => 
                    if rising_edge(start)  then
                        nextstate <= AA;
                    end if;
                        
                when AA =>
                    if (a > b and a > c) then
                        nextstate <= BB;
                     else 
                        nextstate <= G;
                    end if;
                when BB => 
                        ULAOP <= '1';
                        M1 <= "011";
                        M2 <= "10"; --FEITO
                        acc <= '1';
                        nextstate <= CC;
                when CC => 
                        ULAOP <= '1'; --FEITO
                        M1 <= "100";
                        M2 <= "01";
                        acc <= '0';
                        nextstate <= D;
                when D => 
                        ULAOP <= '0';
                        M1 <= "101";
                        M2 <= "11"; --feito
                        acc <= '1';
                        nextstate <= E;
                when E => 
                        ULAOP <= '1';
                        M1 <= "000"; --feito
                        M2 <= "10";
                        acc <= '0';
                        nextstate <= F;
                when F => 
                        ULAOP <= '1';
                        M1 <= "101"; --feito
                        M2 <= "11";
                        acc <= '1';
                        nextstate <= IDLE;
                        
                 when G => 
                        ULAOP <= '1';
                        M1 <= "000"; --feito RAIZ COMEÇA AQUI
                        M2 <= "01";
                        acc <= '0';
                        nextstate <= H;
                 when H => 
                        ULAOP <= '1';
                        M1 <= "101"; 
                        M2 <= "10"; --feito
                        acc <= '1';
                        nextstate <= IDLE;

            end case;
  end  process next_state;     
end rtl; 
