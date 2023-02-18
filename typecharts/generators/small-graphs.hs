import Control.Monad
import Data.Array
import Data.List
import Data.Monoid
import Data.Ratio
import Text.Printf hiding (toChar)
import qualified Data.Set as S

nubFast :: Ord a => [a] -> [a]
nubFast = S.toList . S.fromList

data Label = X | M | E | P deriving (Eq, Ord, Show, Enum)

fromFrac :: Rational -> Label
fromFrac x = if x == 0 then X else if x == 1 then E else if x < 1 then M else P

toFrac :: Label -> Rational
toFrac = ([0,1%2,1,2] !!) . fromEnum

toChar :: Label -> Char
toChar = ("x-=+" !!) . fromEnum

instance Monoid Label where
    mempty = E
    mappend a b = fromFrac (toFrac a * toFrac b)

type Graph = [(Int,Int,Label)]

-- Generates all connected graphs with given number of nodes and set of edge labels,
-- where self loops are either allowed or not. Skips graphs for which the edge labels
-- are inconsistent.

smallGraphs :: [Label] -> Bool -> Int -> [Graph]
smallGraphs labels allowSelfLoops 1 = [] : if allowSelfLoops then [[(1,1,x)] | x <- labels] else []
smallGraphs labels allowSelfLoops n = nubFast $ map canonize $ filter isValid candidates
    where
        extraEdges = do
            xs <- delete [n] $ tail $ subsequences [1 .. if allowSelfLoops then n else n-1]
            ys <- replicateM (length xs) labels
            return $ zip3 (repeat n) xs ys
        
        candidates = (++) <$> extraEdges <*> smallGraphs labels allowSelfLoops (n-1)
        
        assignments = map (listArray (1,n)) $ replicateM n labels
        satisfies g a = all (\(u,v,x) -> x == a!u <> a!v) g
        isValid g = any (satisfies g) assignments
        
        relabelings = map (listArray (1,n)) $ permutations [1..n]
        relabel g p = map (\(u,v,x) -> let u' = p!u; v' = p!v in (min u' v', max u' v', x)) g
        canonize g = minimum $ map (sort . relabel g) relabelings

-- Build test cases as the disjoint union of all graphs from a certain class.

size :: Graph -> Int
size g = maximum $ 1 : [max u v | (u,v,_) <- g]

combine :: [Graph] -> Graph
combine gs = concat $ snd $ mapAccumL step 0 gs
    where step n g = (n + size g, map (\(u,v,x) -> (n+u,n+v,x)) g)

testCase :: [Label] -> Bool -> Int -> Graph
testCase labels allowSelfLoops n = combine $ concatMap (smallGraphs labels allowSelfLoops) [1..n]

testCases :: [Graph]
testCases = [ testCase [M,E,P] True 4
            , testCase [M,E,P] False 5
            , testCase [M,E] True 5
            , testCase [E,P] False 6
            ]

printGraph :: Graph -> IO ()
printGraph g = do
    printf "%d %d\n" (size g) (length g)
    forM_ g $ \(u,v,x) -> printf "%d %d %c\n" u v (toChar x)

main :: IO ()
main = do
    k <- readLn
    printGraph (testCases !! k)
