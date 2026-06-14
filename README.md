var trame;
var data;
trame = msg.payload.split("");
if (trame[0] == "FLM420I;0210502") {
data = ((trame[1] + 4) * 27 / 1.8).toFixed(1);
msg.payload = { "chlore": data };
    return msg;
}
