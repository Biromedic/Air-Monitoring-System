import pandas as pd
from io import StringIO

data = """
Temperature (C),Humidity (%)
#data's go here as temperature , humidity
"""

df = pd.read_csv(StringIO(data))

df.to_excel("simulation_data.xlsx", index=False)

print("successfull written")
