"""
https://community.plotly.com/t/2-plots-same-x-axis-different-y-axis-merge-them-to-same-file/30967
"""
from plotly.subplots import make_subplots
import plotly.graph_objects as go
import pandas as pd

fig = make_subplots(rows=1, cols=2,  specs=[[{"type": "xy", "secondary_y":True}, {"type": "table", "secondary_y":False}]], column_widths=[2,1])

df = pd.read_csv('data.csv')

# Add first scatter trace
fig.add_trace(go.Scatter(
    x=df["Current [A]"],
    y=df["Power [W]"],
    mode="markers+lines",
    name="Power [W]",
    marker=dict(color="blue")),
    secondary_y=False,
    row=1, col=1)

# Add second scatter trace with a secondary y-axis
fig.add_trace(go.Scatter(
    x=df["Current [A]"],
    y=df["PW [ns]"],
    mode="markers+lines",
    name="Pulse width [ns]",
    marker=dict(color="red")),
    secondary_y=True, 
    row=1, col=1)

# Update layout for dual y-axes
fig.update_layout(
    xaxis=dict(title="Current [A]", domain=[0,.62], tickfont=dict(color="black", size=15)),
    yaxis=dict(title="Power [W]", tickfont=dict(color="blue", size=15)),
    yaxis2=dict(
        title="Pulse Width [ns]",
        tickfont=dict(color="red", size=15),
        overlaying="y",
        side="right",
    ),
    legend=dict(y=.5, x=.5),
    margin=dict(l=100, r=100, t=100, b=100),
    hovermode='x'
)

fig.add_trace(go.Table(
    header=dict(values=["Current [A]", "Power [W]", "Pulse Width [ns]"],
                font=dict(size=18),
                fill_color="lightgrey",
                align="center",
                height=40),
    cells=dict(values=[df["Current [A]"], df["Power [W]"], df["PW [ns]"]],
               font=dict(size=15),
               fill_color="white",
               align="center",
               height=32),
    ),
    row=1,col=2)

fig.update_layout(height=600)

fig.update_layout(
    title=dict(
        text="Power / Pulse Data",
        font=dict(size=30)
        ),
    xaxis=dict(
        title=dict(
            text="Current [A]",
            font=dict(size=15)
        )
    ),
    yaxis=dict(
        title=dict(
            text="Power [W]",
            font=dict(size=15)
        ),
        color='blue'
    ), 
    yaxis2=dict(
        title=dict(
            text="Pulse Width [ns]",
            font=dict(size=15) 
            ),
        color='red'
    ),
    font=dict(
        family="Times New Roman"
        )
)


fig.update_traces(domain_x=[.66, 1], domain_y=[0,1], selector=dict(type='table'))

#fig.update_layout(
#    font_family="Times New Roman",
#    font_color="black",
#    title_font_family="Times New Roman",
#    title_font_color="black",
#    legend_title_font_color="black"
#)

fig.show()
