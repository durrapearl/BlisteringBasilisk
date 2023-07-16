#Stage1 Proposal

InfluxDB + GRAFANA DASHBOARD
https://datalogd.readthedocs.io/en/latest/recipes/win_serial_influxdb_grafana.html


![Figma basics (1)](https://user-images.githubusercontent.com/124263652/236239072-c0fcc080-756f-4efd-9e24-2e5d5f78a83b.png)

Step 1: Install Python and Git
Ensure you have Python and Git installed on your Linux machine. If they are not already installed, you can install them using the package manager provided by your Linux distribution. For example, on Ubuntu, you can use the following commands:

sudo apt-get update

sudo apt-get install python3 git

Step 2: Clone the Repository
Open the terminal on your Linux system and use the git clone command to clone the project repository. Run the following command:


git clone https://github.com/durrapearl/BlisteringBasilisk.git


Step 3: Set Environment Variables

Make sure to set the environment variable INFLUXDB_TOKEN with the appropriate value. This token is used to authenticate with InfluxDB when sending data. Replace [your_influxdb_token] with your actual InfluxDB token.


export INFLUXDB_TOKEN=[your_influxdb_token]

Step 5: Run the Code

The project contains two Python scripts: one for the Wio device (wio.py) and the other to receive and send data to InfluxDB (datatoinflux.py).

To run the Wio device script, execute the following:

python wio.py

To run the script that receives data and sends it to InfluxDB, execute the following:

python datatoinflux.py


Step 6: Set up InfluxDB and Grafana

Before running the scripts, ensure you have InfluxDB and Grafana set up and running on your machine or accessible from your Linux system. Make sure that the InfluxDB URL (http://172.17.0.1:8086) in the Python scripts matches your InfluxDB server address.

Step 7: Create Grafana Dashboard

To visualize the data, you need to create a Grafana dashboard. Copy the provided Grafana query and create a new panel in Grafana using that query. The query retrieves data from the InfluxDB bucket "G6" and aggregates the humidity and temperature values over time.

Step 8: View Data in Grafana

Access your Grafana dashboard to see the data visualizations based on the data received from the Wio device and stored in InfluxDB.
