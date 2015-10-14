windowSize = 10;
ourVal = csvread('out30.txt', 0 ,1 , [0 1 1400 1]);
measurements = csvread('out30.txt', 0, 0, [0 0 1400 0]);

filterEq = (1/windowSize)*ones(1,windowSize);

filterVal = filter(filterEq, 1, measurements);

%t = linspace(100, 2000);

plot(ourVal)
hold on
plot(filterVal)

grid on
legend('ourVal', 'filterVal', 'Location', 'NorthWest')


diff = filterVal - ourVal;

mean(diff)
std(diff)