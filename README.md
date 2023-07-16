#Stage1 Proposal

InfluxDB + GRAFANA DASHBOARD
https://datalogd.readthedocs.io/en/latest/recipes/win_serial_influxdb_grafana.html


![Figma basics (1)](https://user-images.githubusercontent.com/124263652/236239072-c0fcc080-756f-4efd-9e24-2e5d5f78a83b.png)

Query in Grafana:

from(bucket: "G6")
  |> range(start: v.timeRangeStart, stop: v.timeRangeStop)
  |> filter(fn: (r) => r["_measurement"] == "DHT_data")
  |> filter(fn: (r) => r["_field"] == "humidity" or r["_field"] == "temperature")
  |> filter(fn: (r) => r["location"] == "Outdoor")
  |> aggregateWindow(every: v.windowPeriod, fn: mean, createEmpty: false)
  |> yield(name: "mean")
