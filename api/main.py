#!/usr/bin/env python
# encoding: utf-8

# METHODS
# @app.route('/', methods=['GET'])
# @app.route('/', methods=['PUT'])
# @app.route('/', methods=['POST'])
# @app.route('/', methods=['DELETE'])

# https://pythonbasics.org/flask-rest-api/


import json
from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/')
def index():
    data = request.args
    print(data)
    return json.dumps(data)


@app.route('/', methods=['POST'])
def create_record():
    record = json.loads(request.data)
    with open('/tmp/data.txt', 'r') as f:
        data = f.read()
    if not data:
        records = [record]
    else:
        records = json.loads(data)
        records.append(record)
    with open('/tmp/data.txt', 'w') as f:
        f.write(json.dumps(records, indent=2))
    return jsonify(record)


if __name__ == "__main__":
    app.run(debug=True, port=5000, host='0.0.0.0')