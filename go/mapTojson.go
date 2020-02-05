package main

import (
    "fmt"
    "encoding/json"
)

type ActionResult struct {
    Action       string                  `json:"action"`
    ResultMap    map[string]interface{}  `json:"map_result"`
}

type ProcessResult struct {
    PreProcessGuid      string                   `json:"preprocess_guid"`
    PreProcessResMap    map[string]ActionResult  `json:"preprocess_result"`
}



func main() {

    process := &VodFileSeg{}

    process.PreProcessGuid = "123456788"
    s :=[] float64 {1.1, 1.2, 1.3, 1.4}

    str := "hahha,is a test!!!"

    process.ExtractTime = make(map[string]ProcessResult)

    a := ProcessResult{}
    a.Action = "extract_time"
    a.SegmentTime = make(map[string]interface{})
    a.SegmentTime["1"] = s

    
    process.ExtractTime["extract_time"] = a

    b := ProcessResult{}
    b.Action = "test"
    b.SegmentTime = make(map[string]interface{})
    b.SegmentTime["fff"] = str

    process.ExtractTime["Ha_test"] = b
    

    data, _ := json.Marshal(process)

    fmt.Printf("[%+v]\n", string(data))

}



