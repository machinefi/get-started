package main

import (
	"fmt"
	"strings"

	"github.com/tidwall/gjson"

	common "github.com/machinefi/w3bstream/_examples/wasm_common_go"
)

func main() {}

//export start
func handler(event_id uint32) int32 {
	// Log the call
	common.Log(fmt.Sprintf("W3bstream logic called with Event Id: %d", event_id))
	// Get the event message payload
	message, err := common.GetDataByRID(event_id)
	if err != nil {
		common.Log("error: " + err.Error())
		return -1
	}
	// Convert the payload to a string
	res := string(message)
	// Log the account address to send tokens to
	Account := gjson.Get(res, "Account").String()
	common.Log(fmt.Sprintf("Account: %s", Account))
	// Get and increment the click count
	count := common.GetDB("clicks") + 1
	// Log the current number of clicks
	common.Log(fmt.Sprintf("Number of clicks: %d", count))
	// Save the new click count
	common.SetDB("clicks", count)

	// Send 1 token to the "Account" address every 5 clicks
	if count%5 == 0 {
		common.Log(fmt.Sprintf("Minting 1 CLICK token to %s", Account))
		common.Log("Sending blockchain tx....")
		result := common.SendTx(fmt.Sprintf(
			`{
				"to": "%s",
				"value": "0",
				"data": "40c10f19000000000000000000000000%s0000000000000000000000000000000000000000000000000de0b6b3a7640000"
			}`,
			//ERC20 "CLICK" tiken contract address
			"0x9AdB43E4Ba7ef5983741C1623e64993848b2Efc5",
			strings.Replace(Account, "0x", "", 1),
		))
		if result == 0 {
			common.Log("tx sent successfully")
		} else {
			common.Log("tx failed")
		}
	}
	return 0
}
