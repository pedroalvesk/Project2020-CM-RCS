#!/usr/bin/env python
# encoding: utf-8

import json
from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/temp')
def temperature():
    data = request.args
    if "value" in data:
        print("[>] Temperatura = " + data["value"])
        return json.dumps(["temperatura", data["value"]])
    else:
        print("[>] Not found")
        return json.dumps("error")

@app.route('/card')
def card():
    data = request.args
    if "value" in data:
        print("[>] Card = " + data["value"])
        return json.dumps(["temperatura", data["value"]])
    else:
        print("[>] Not found")
        return json.dumps("error")

if __name__ == "__main__":
    app.run(debug=True, port=5000, host='0.0.0.0')