import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("results/sortingResultsInt.csv", names=["Test File", "Algorithm", "Data Type", "Time"])
df["mod"] = df["Test File"] % 10

groups = {
    "Test Files 1-4": df[df["mod"].between(1, 4)],
    "Test Files 5-8": df[df["mod"].between(5, 8)],
    "Test Files 9 & 10": df[df["mod"].isin([0, 9])],
}

for title, group_df in groups.items():
    pivot = group_df.pivot(index="Test File", columns="Algorithm", values="Time")
    pivot.plot(kind="bar", figsize=(14, 8), width=0.9)

    plt.title(f"Sorting Algorithm Performance - {title}")
    plt.xlabel("Test File")
    plt.ylabel("Time (seconds, log scale)")
    plt.yscale("log")
    plt.legend(title="Algorithm", bbox_to_anchor=(1.05, 1), loc='upper left')
    plt.xticks(rotation=0)
    plt.grid(axis="y", linestyle="--", alpha=0.7)
    plt.tight_layout()
    plt.savefig(f"results/graph_{title.replace(" ", "_").lower()}_int.png", dpi=200, format="png", bbox_inches="tight")
    plt.close()
