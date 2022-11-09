package main

import (
	"fmt"

	"github.com/tidwall/gjson"

	common "github.com/machinefi/w3bstream/_examples/wasm_common_go"
)

func main() {}

//export start
func _start(rid uint32) int32 {
	common.Log(fmt.Sprintf("start received: %d", rid))
	message, err := common.GetDataByRID(rid)
	if err != nil {
		common.Log("error: " + err.Error())
		return -1
	}
	res := string(message)

	Account := gjson.Get(res, "Account")
	common.Log(fmt.Sprintf("Account: %s", Account.String()))
	count := common.GetDB("clicks") + 1

	common.Log(fmt.Sprintf("number of clicks: %d", count))

	common.SetDB("clicks", count)

	if count%5 == 0 {
		common.Log("sending tx....")
		common.SendTx(fmt.Sprintf(
			`{
				"to": "%s",
				"value": "0",
				"data": "40c10f19000000000000000000000000%s0000000000000000000000000000000000000000000000000de0b6b3a7640000"
			}`,
			"0x3Fb8306Ca5C7d5A752b195F1df2f03CCE6BC1Bcb", //W3BERC20 contract address
			Account.String(), //send to account
		))
		common.Log("tx sent successfully")
	}

	return 0
}
