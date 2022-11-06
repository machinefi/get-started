// W3bstream logic to handle the device message
package main

import (
	"fmt"

	common "github.com/machinefi/w3bstream/_examples/wasm_common_go"
	"github.com/tidwall/gjson"
)

func main() {}

// Exported function to serve as a W3bstream handler
func _start(event_id uint32) int32 {
	common.Log(fmt.Sprintf("start handler called with event id: %d", event_id))
	// Get the payload attached to the W3bstream event message
	payload, err := common.GetDataByRID(event_id)
	if err != nil {
		common.Log("Error while getting event data: " + err.Error())
		return -1
	}
	res := string(payload)

	// Get the recipient address from the payload
	Account := gjson.Get(res, "Account")
	// Get the current number of clicks from the key-value store
	count := common.GetDB("clicks") + 1
	common.Log(fmt.Sprintf("Current number of clicks: %d", count))
	// Update the number of clicks in the key-value store
	common.SetDB("clicks", count)
	// Send the reward to the recipient address every 5 clicks
	if count%5 == 0 {
		common.Log("Sending rewards transaction....")
		common.SendTx(fmt.Sprintf(
			`{
				"to": "%s",
				"value": "0",
				"data": "40c10f19000000000000000000000000%s0000000000000000000000000000000000000000000000000de0b6b3a7640000"
			}`,
			// Mintable token contract address
			"0x3Fb8306Ca5C7d5A752b195F1df2f03CCE6BC1Bcb",
			// Recipient account, indicated in the device message
			Account.String(),
		))
		common.Log("Transaction sent.")
	}

	return 0
}
