clear all;
clc;


windowSize = 50;

% ourVal = csvread('out10.txt', 0 ,1 , [0 1 1286 1]);
% measurements = csvread('out10.txt', 0, 0, [0 0 1286 0]);

% ourVal = csvread('out20.txt', 0 ,1 , [0 1 1120 1]);
% measurements = csvread('out20.txt', 0, 0, [0 0 1120 0]);


% ourVal = csvread('out25.txt', 0 ,1 , [0 1 996 1]);
% measurements = csvread('out25.txt', 0, 0, [0 0 996 0]);


% ourVal = csvread('out30.txt', 0 ,1 , [0 1 1141 1]);
% measurements = csvread('out30.txt', 0, 0, [0 0 1141 0]);

% ourVal = csvread('out40.txt', 0 ,1 , [0 1 2175 1]);
% measurements = csvread('out40.txt', 0, 0, [0 0 2175 0]);

% ourVal = csvread('out50.txt', 0 ,1 , [0 1 1399 1]);
% measurements = csvread('out50.txt', 0, 0, [0 0 1399 0]);


filterEq = (1/windowSize)*ones(1,windowSize);

filterVal = filter(filterEq, 1, measurements);

plot(ourVal)
hold on
plot(filterVal)
plot(measurements)
grid on
legend('ourVal', 'filterVal', 'measurements', 'Location', 'NorthWest')


diff = filterVal - ourVal;

mean(diff)
std(diff)