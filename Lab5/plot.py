import matplotlib.pyplot as plt

# Read data from file
file_path = "log.txt"  # Replace "data.txt" with your file path
x_values = []
y_values = []
with open(file_path, 'r') as file:
    for line in file:
        y, x = map(float, line.strip().split())
        x_values.append(x)
        y_values.append(y)

# Plot data
plt.plot(x_values, y_values, linestyle='solid')
plt.xlabel('X Axis')
plt.ylabel('Y Axis')
plt.title('Plot with X and Y Axis')
plt.grid(True)
plt.show()