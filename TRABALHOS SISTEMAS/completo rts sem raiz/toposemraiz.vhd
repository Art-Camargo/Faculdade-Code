----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 04.12.2023 20:49:26
-- Design Name: 
-- Module Name: TOPO - Behavioral
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

entity TOPO is
    Port ( 
        clk, start : in std_logic;
        a, b, c: in integer;
        z: out integer
    );
end TOPO;

architecture rtl of TOPO is
    signal acc_s: std_logic;
    signal a_s: integer ;
    signal b_s: integer;
    signal c_s: integer;
    signal z_s: integer;
    signal M2_s: std_logic_vector(1 downto 0);
    signal ULAOP_s: std_logic;
    signal M1_s: std_logic_vector(2 downto 0);
    
    component UnidadeOperativa is 
    port (
       clk, acc: in std_logic;
       a, b, c: in integer;
       M2: in std_logic_vector(1 downto 0);
       ULAOP: in std_logic;
       M1: in std_logic_vector(2 downto 0);
       Z: out integer
    );
    end component;

    component UnidadeControle is 
         port (
             ULAOP: out std_logic;
             M2: out std_logic_vector(1 downto 0);
             acc: out std_logic;
             M1: out std_logic_vector(2 downto 0);
             start: in std_logic;
             clk: in std_logic;
             a, b, c: in integer
        );
    end component;
    
    
begin
    
    a_s <= a;
    b_s <= b;
    c_s <= c;
    
    UnidadeOperativaTrabalho_i : UnidadeOperativa
    port map (
        
        clk => clk,
        acc => acc_s,
        a => a_s,
        b => b_s,
        c => c_s,
        M1 => M1_s,
        M2 => M2_s,
        ULAOP => ULAOP_s,
        Z => z_s
    );
    
    
    UnidadeControle_i : UnidadeControle
    port map(
        M1 => M1_s,
        M2 => M2_s,
        ULAOP => ULAOP_s,
        acc => acc_s,
        clk => clk,
        start => start,
        a => a_s,
        b => b_s,
        c => c_s
    );
end rtl;
