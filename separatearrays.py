import json

# Load the JSON data
with open('palavras.json', 'r') as file:
    data = json.load(file)

# Identify and split the specific field into an array
for item in data:
    item['words'] = item['words'].split(' ')

# Save the modified data back to a JSON file
with open('languages.json', 'w') as file:
    json.dump(data, file, separators=(',', ':'))

