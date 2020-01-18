package main

import (
    "fmt"
    "encoding/json"
)


var a string = `{
    "guid":"dfsdfsdlkfjdsfjaldsfasdf",
    "data":{
        "failed_desc":[
            {
                "action":"ttttt",
                "cause":"fffff not found",
                "details":[
                    "www.baidu.com/1111/2222",
                    "wwww.baidu.com/2222/333333"
                ]
            },
            {
                "action":"tddddddd",
                "cause":"1123213",
                "details":[
                    "www.bbbb.com/11111/22222",
                    "dsafafdafafafafaf"
                ]
            }
        ]
    },
    "errmsg":"error msg",
    "errno":5
}`


type FailedDesc struct{
    FailedAction   string    `json:"action"`
    FailedCause    string    `json:"cause"`
    FailedDetials  []string  `json:"details"`

}

type DataFailedDesc struct {
    FailedDesc  []FailedDesc  `json:"failed_desc"`
}


type Body struct {
    PreProcess_guid string         `json:"guid"`
    Data            DataFailedDesc `json:"data"`
    ErrorMsg        string         `json:"errmsg"`
    ErrorNO         int            `json:"errno"`
}



func main() {
    var test Body

    json.Unmarshal([]byte(a), &test)

    fmt.Println(test.Data.FailedDesc[0].FailedAction)
    fmt.Println(test.Data.FailedDesc[0].FailedCause)
    fmt.Println(test.Data.FailedDesc[0].FailedDetials[0])
    fmt.Println(test.Data.FailedDesc[0].FailedDetials[1])
}






































